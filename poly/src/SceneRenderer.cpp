#include "SceneRenderer.h"

#include <osgDB/ReadFile>

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>

#include <osg/MatrixTransform>
#include <osg/BoundingSphere>

#include <iostream>
#include <sstream>
#include <string>

#include <alice/InputHandler.h>

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
			while(std::getline(file,line,',') && !line.empty()){
				osg::MatrixTransform* scale = new osg::MatrixTransform();
				// this next matrix will actually hold both translation and rotation (one operation must be applied from the left, the other from the right of the identity.
				osg::MatrixTransform* translation = new osg::MatrixTransform();
				osg::MatrixTransform* model = new osg::MatrixTransform();
				// navigation -> scale -> rotation/translation -> model -> mesh
				mNavTrans->addChild(scale);
				scale->addChild(translation);
				translation->addChild(model);
				model->addChild(osgDB::readNodeFile(line));

				// Conf file reading... probably must be done elsewhere now :(
				std::getline(file,line,','); //first item is the filename, second one is the model type
				if(line == "Model"){
					model->setName("Model Transformation");
				}
				else if(line == "World"){
					model->setName("World Transformation");
				}

				float t[3]; // the rest is the translation vector
				for(int i=0; i<3; i++){
					std::getline(file,line,',');
					std::istringstream iss(line);
					iss >> t[i];
				}
				translation->setMatrix(osg::Matrix::translate(t[0],t[1],t[2]));

				float s[3];
				for(int i=0; i<3; i++){
					std::getline(file,line,',');
					std::istringstream iss(line);
					iss >> s[i];
				}
				scale->setMatrix(osg::Matrix::scale(s[0],s[1],s[2]));
				std::getline(file,line); // fetch one more time to reach the end of line.
			}
		}

		void SceneRenderer::contextInit(){
			const unsigned int unique_context_id = mInput->getCurrentContext();
			// This is the object that will be in charged of rendering everything
			osg::ref_ptr<osgUtil::SceneView> sv(new osgUtil::SceneView);
			sv->setDefaults(osgUtil::SceneView::STANDARD_SETTINGS);

			sv->setFrameStamp(mFrameStamp.get()); // Need to do this before init

			sv->init();
			sv->setClearColor(osg::Vec4( 0, 0, 0, 0 ));
			sv->setDrawBufferValue(GL_NONE); // Needed for stereo to work

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

			// center the scene
			if(mInput->centerModels()){
				osg::BoundingSphere bs = mRootNode->getBound();
				osg::Vec3 center = bs.center();
				std::cout << "BoundingSphere Radius: " << bs.radius() <<" Center: X(" << center[0] << ") Y(" << center[1] << ") Z(" << center[2] <<")\n";

				osg::Matrix currentNav = mNavTrans->getMatrix();
				osg::Matrix offset = osg::Matrix::translate(-center[0],-center[1],-center[2]);

				mNavTrans->setMatrix(offset * currentNav);

				mInput->centerModels(false);	// Only do it once per button click
			}

			// Update the navigation matrix
			if(mInput->applyNavigation()){
				mNavTrans->setMatrix(convertMatrix(mInput->navigationMatrix()));
				mRootNode->getBound();
			}
			
			// Intersection check
			if( mInput->applySelectionTest()){
				osg::Vec3d start = convertVector(mInput->getRayStart());
				osg::Vec3d end = convertVector(mInput->getRayEnd());
				osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(start, end);
				osgUtil::IntersectionVisitor intersectVisitor( intersector.get() );
				mRootNode->accept(intersectVisitor);

				// What to do with the selected object
				if( intersector->containsIntersections() ){
					osgUtil::LineSegmentIntersector::Intersection intersection = intersector->getFirstIntersection();
					// mRootNode -- mNavTrans -- scale -- rotation/translation -- mModel
					if(intersection.nodePath[4]->asTransform()->asMatrixTransform()->getName() == "Model Transformation"){
						mSelectedObjectTransformation = intersection.nodePath[3]->asTransform()->asMatrixTransform();
						mInput->selectedObjectTransformation(convertMatrix(mSelectedObjectTransformation->getMatrix()));

						mSelectedObjectScaling = intersection.nodePath[2]->asTransform()->asMatrixTransform();
						mInput->selectedObjectScalingMatrix(convertMatrix(mSelectedObjectScaling->getMatrix()));
						
						mInput->objectSelected(true);						//we intersected something manipulable
					} else {
						mInput->objectSelected(false);			//intersecting a non-manipulable object
					}
				} else mInput->objectSelected(false);				//not intersecting anything
			}

			// The manipulation method needs to let us know if there is any manipulation to do
			if(mInput->applyManipulation()){
				mSelectedObjectTransformation->setMatrix(convertMatrix( mInput->selectedObjectTransformation() ));
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
