/******************************************************************************
 *
 *	This library is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include "SceneRenderer.h"

#include <osgDB/ReadFile>

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>

#include <osg/MatrixTransform>

#include <iostream>
#include <string>

#include <alice/InputHandler.h>

#include "Utils.h"

namespace alice {

    namespace poly {

        void SceneRenderer::init(InputHandler* input){
            // The parent class's init mehtod just stores the input object
            alice::SceneRenderer::init(input);

            mUpdateVisitor = new osgUtil::UpdateVisitor();
            mFrameStamp    = new osg::FrameStamp();
            mUpdateVisitor->setFrameStamp(mFrameStamp.get());

            // This is the structure of the scene graph
            // mRootNode -- mNavTrans -- mModelTrans -- mModel
            mRootNode = new osg::Group();
            mNavTrans = new osg::MatrixTransform();
            mRootNode->addChild(mNavTrans.get());

            std::string line;
            std::ifstream file(mSceneConfigurationFile.c_str());
            while(std::getline(file,line,',')){
                if(!line.empty()){
                    std::cout << "Loading Model: " << line << std::endl;
                    //osg::MatrixTransform* newModel;
                    mModelTrans = new osg::MatrixTransform();
                    mModelTrans->addChild(osgDB::readNodeFile(line));
                    std::getline(file,line);
                    if(line == "Model"){
                        mModelTrans->setName("Model Transformation");
                        std::cout << "Model Type: Model" << std::endl;
                    }
                    else if(line == "World"){
                        mModelTrans->setName("World Transformation");
                        std::cout << "Model Type: World" << std::endl;
                    }
                    mNavTrans->addChild(mModelTrans.get());
                }
            }

            // Shader stuff
            programObject = new osg::Program();

            vertexObject = new osg::Shader(osg::Shader::VERTEX);
            vertexObject->loadShaderSourceFromFile(
                    osgDB::findDataFile("share/shaders/poly/homography.vert"));
            programObject->addShader(vertexObject);

            fragmentObject = new osg::Shader(osg::Shader::FRAGMENT);
            fragmentObject->loadShaderSourceFromFile(
                    osgDB::findDataFile("share/shaders/poly/homography.frag"));
            programObject->addShader(fragmentObject);


            rootStateSet = mRootNode->getOrCreateStateSet();

            rootStateSet->setAttributeAndModes(programObject, osg::StateAttribute::ON);
            rootStateSet->addUniform(new osg::Uniform("homographyMatrix", osg::Matrix(
                    utils::loadHomographyFromFile(osgDB::findDataFile("share/shaders/poly/homography.txt")))));

            osg::Uniform* texUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D,"Texture");
            texUniform->set(0);
            rootStateSet->addUniform(texUniform);
        }

        void SceneRenderer::contextInit(){
            const unsigned int unique_context_id = mInput->getCurrentContext();

            // This is the object that will be in charged of rendering everything
            osg::ref_ptr<osgUtil::SceneView> sv(new osgUtil::SceneView);

            sv->setDefaults(osgUtil::SceneView::STANDARD_SETTINGS);

            sv->setFrameStamp(mFrameStamp.get());	// Need to do this before init

            sv->init();
            sv->setClearColor(osg::Vec4( 0.5f, 0.8f, 1.0f, 1.0f ));

            sv->setDrawBufferValue(GL_NONE);	// Needed for stereo to work

            // Set the light
            sv->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
            sv->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
            sv->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
            sv->getLight()->setPosition(osg::Vec4(0.0f,2.0f,0.0f,1.0f));

            // We tell it its context id
            sv->getState()->setContextID(unique_context_id);

            // Add the tree to the scene viewer and set properties
            mInput->lockMutex();
            sv->setSceneData(mRootNode.get());
            mInput->releaseMutex();

            // Set the configured scene viewer object to the context specific pointer.
            (*sceneViewer) = sv;
        }

        void SceneRenderer::latePreFrame(){
            // Time updates
            mFrameStamp->setFrameNumber(++mFrameNumber);
            mFrameStamp->setReferenceTime(mInput->getCurrentTimeStamp());
            mFrameStamp->setSimulationTime(mInput->getCurrentTimeStamp());

            mUpdateVisitor->setTraversalNumber(mFrameNumber);
            mRootNode->accept(*mUpdateVisitor);

            // Update the navigation matrix
            if(mInput->applyNavigation()){
                mNavTrans->setMatrix(utils::convertMatrix(mInput->navigationMatrix()));
                mRootNode->getBound();
            }

            // Intersection check
            if( mInput->applySelectionTest() ){
                //std::cout << "Intersecting\n";
                gmtl::Vec3f s = mInput->getRayStart();
                gmtl::Vec3f e = mInput->getRayEnd();
                osg::Vec3d start(s[0],s[1],s[2]);
                osg::Vec3d end(e[0],e[1],e[2]);
                osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
                        new osgUtil::LineSegmentIntersector(start, end);
                osgUtil::IntersectionVisitor intersectVisitor( intersector.get() );
                mRootNode->accept(intersectVisitor);

                // What to do with the selected object
                if( intersector->containsIntersections() ){
                    osgUtil::LineSegmentIntersector::Intersection intersection = intersector->getFirstIntersection();
                    // 0						1						 2							3
                    // mRootNode -- mNavTrans --  mModelTrans -- mModel
                    if(intersection.nodePath[2]->asTransform()->asMatrixTransform()->getName() == "Model Transformation"){
                        mSelectedObjectTransformation = intersection.nodePath[2]->asTransform()->asMatrixTransform();
                        mInput->selectedObjectTransformation(utils::convertMatrix(mSelectedObjectTransformation->getMatrix()));
                        mInput->objectSelected(true);						//we intersected something manipulable
                    } else mInput->objectSelected(false);			//intersecting a non-manipulable object
                }	else mInput->objectSelected(false);				//not intersecting anything
            }

            // The manipulation method needs to let us know if there is any manipulation to do
            if(mInput->applyManipulation()){
                //std::cout << "Manipulating\n";
                mSelectedObjectTransformation->setMatrix(utils::convertMatrix( mInput->selectedObjectTransformation() ));
                mRootNode->getBound();
            }

        }

        void SceneRenderer::draw() {
            osg::ref_ptr<osgUtil::SceneView> sv;
            sv = (*sceneViewer);	// Get context specific scene viewer

            if(sv.get() != NULL){
                sv->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);

                const int* viewport = mInput->getViewport();
                sv->setViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
                const float* frustum = mInput->getFrustum();
                sv->setProjectionMatrixAsFrustum(frustum[0], frustum[1], frustum[2], frustum[3], frustum[4], frustum[5]);
                sv->setViewMatrix(osg::Matrix(mInput->getViewMatrix()));

                sv->cull();
                sv->draw();
            }
        }
    }
}
