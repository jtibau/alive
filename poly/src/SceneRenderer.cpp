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

#include <osgDB/FileUtils>	//to load the shaders

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>

#include <osg/MatrixTransform>
#include <osg/CopyOp>

#include <iostream>
#include <fstream>

#include <alice/InputHandler.h>

namespace alice {

	namespace poly {

		// we don't want this right now
		float* loadHomographyFromFile(std::string file){

		  std::cout << "Archivo Homografia: " << file << std::endl;
			float* homography = new float[16];
			
			std::string line;
			std::ifstream data(file.c_str());
			
			for(int i=0; i<16; i++){
				std::getline(data,line,':');
				
				std::istringstream iss(line);
				float f;
				iss >> std::dec >> f;
				homography[i] = f;
				
				std::cout << f << "\t";
				if(i%4 == 3) std::cout << "\n";
			}
			std::cout << "\n\n";
			return homography;
		}


		void SceneRenderer::init(InputHandler* input){

			// The parent class's init mehtod just stores the input object
			alice::SceneRenderer::init(input);

			// The code here is independent of context, it is purely related to
			// the object database. Nothing is loaded into the gl contexts.
			
			mUpdateVisitor = new osgUtil::UpdateVisitor();
			mFrameStamp    = new ::osg::FrameStamp();
			mUpdateVisitor->setFrameStamp(mFrameStamp.get());

			// This is the structure of the scene graph
			// mRootNode
			//         \-- mNavTrans -- mModelTrans -- mModel
			//						\-- mHouseTrans -- mHouse
			mRootNode = new osg::Group();
			mNavTrans = new osg::MatrixTransform();
			mRootNode->addChild(mNavTrans.get());

			//mModel = osgDB::readNodeFile("share/data/stand.3DS");
			mModelTrans  = new osg::MatrixTransform();
			mModelTrans->setName("Model Transformation");	// Used in order to make some nodes moveable
			mModelTrans->addChild(osgDB::readNodeFile("share/data/stand.3DS"));
			mNavTrans->addChild(mModelTrans.get());

			//mHouse = osgDB::readNodeFile("share/data/casa.3DS");
			mHouseTrans = new osg::MatrixTransform();
			mHouseTrans->setName("World Transformation");
			mHouseTrans->addChild(osgDB::readNodeFile("share/data/casa.3DS"));
			mNavTrans->addChild(mHouseTrans.get());
			
			// Shader stuff
			rootStateSet = mRootNode->getOrCreateStateSet();
			rootStateSet->ref();
			
			programObject = new osg::Program();

			vertexObject = new osg::Shader(osg::Shader::VERTEX);
			programObject->addShader(vertexObject);

			fragmentObject = new osg::Shader(osg::Shader::FRAGMENT);
			programObject->addShader(fragmentObject);
			
			std::string vertPath = osgDB::findDataFile("share/shaders/poly/homography.vert");
			std::string fragPath = osgDB::findDataFile("share/shaders/poly/homography.frag");
			
			if( vertexObject->loadShaderSourceFromFile(vertPath) )
				std::cout << vertPath << std::endl ;
			if( fragmentObject->loadShaderSourceFromFile(fragPath) )
				std::cout << fragPath << std::endl;
			
			rootStateSet->setAttributeAndModes(programObject, osg::StateAttribute::ON);
			
			float *homography1 = loadHomographyFromFile( osgDB::findDataFile("share/shaders/poly/homography.txt"));
			osg::Uniform* uniHomography1 = new osg::Uniform("homographyMatrix",osg::Matrix(homography1));
			rootStateSet->addUniform(uniHomography1);

			osg::Uniform* texUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D,"Texture");
			texUniform->set(0);
			rootStateSet->addUniform(texUniform);

		}

		void SceneRenderer::contextInit(){
			// Now this is real gl code
			// The purpose of the calls here is to get the graphics pipelines ready for rendering
			
			// The id of the context will be given to the context specific objects
			const unsigned int unique_context_id = mInput->getCurrentContext();

			// --- Create new context specific scene viewer -- //
			// This is the object that will be in charged of rendering everything
			::osg::ref_ptr<osgUtil::SceneView> new_sv(new osgUtil::SceneView);
			
			{
				osgUtil::SceneView* newSceneViewer = new_sv.get();
				newSceneViewer->setDefaults(osgUtil::SceneView::STANDARD_SETTINGS);

				// Set the timing information in the scene view. This has to be done
				// only once per osgUtil::SceneView instance and should be done before
				// calling osgUtil::SceneView::init().
				newSceneViewer->setFrameStamp(mFrameStamp.get());

				newSceneViewer->init();
				// A sort of sky color for the background (or change it to black, people didn't like this blue)
				newSceneViewer->setClearColor(::osg::Vec4(135.0f/256.0f, 206.0f/256.0f, 250.0f/256.0f, 1.0f));

				// Needed for stereo to work.
				newSceneViewer->setDrawBufferValue(GL_NONE);

				// Set the light
				// Bear in mind that this light follows the camera...
				// its position is not affected by the navigation matrix
				newSceneViewer->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
				newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
				newSceneViewer->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
				newSceneViewer->getLight()->setPosition(osg::Vec4(0.0f,5.0f,0.0f,1.0f));
			}

			// We tell it its context id
			new_sv->getState()->setContextID(unique_context_id);

			// Add the tree to the scene viewer and set properties
			{
				// should change this mutex for something vrjuggler-independent
				//vpr::Guard<vpr::Mutex> sv_guard(mSceneViewLock);
				mInput->lockMutex();
				new_sv->setSceneData(mRootNode.get());
				mInput->releaseMutex();
			}

			// And we set our newly configured scene viewer object on to the context specific pointer.
			(*sceneViewer) = new_sv;
			
			std::cout << "Context initted\n";
		}

		// This convertion methods are not to be used outside these files
		// Outside objects shouldn't even be aware that we use osg
		gmtl::Matrix44f convertMatrix(osg::Matrix original){
			original.invert(original);
			gmtl::Matrix44f converted;
			converted.set(original(0,0),original(1,0),original(2,0),original(3,0),
										original(0,1),original(1,1),original(2,1),original(3,1),
										original(0,2),original(1,2),original(2,2),original(3,2),
										original(0,3),original(1,3),original(2,3),original(3,3));

			return converted;
		}
		
		// Ditto above
		osg::Matrix convertMatrix(gmtl::Matrix44f original){
			osg::Matrix converted(original.getData());
			converted.invert(converted);
			return converted;
		}


		void SceneRenderer::latePreFrame(){
			// The update code

			// Time updates
			const double head_time = mInput->getCurrentTimeStamp();
			++mFrameNumber;

			// Update the frame stamp with information from this frame.
			mFrameStamp->setFrameNumber(mFrameNumber);
			mFrameStamp->setReferenceTime(head_time);
			mFrameStamp->setSimulationTime(head_time);

			mUpdateVisitor->setTraversalNumber(mFrameNumber);
			mRootNode.get()->accept(*mUpdateVisitor);

			// Update the navigation matrix
			if(mInput->applyNavigation()){
				mNavTrans->setMatrix(convertMatrix(mInput->navigationMatrix()));
				mRootNode.get()->getBound();
			}


			if( mInput->applySelectionTest() ){
				// Intersection check
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
					osgUtil::LineSegmentIntersector::Intersection intersection =
							intersector->getFirstIntersection();

					// We remember our graph structure again
					// 0						1						 2							3
					// mRootNode -- mNavTrans -- mModelTrans -- mModel
					//											\	-- mHouseTrans -- mHouse
					// The intersectors nodePath's third level is one of the
					// MatrixTransform nodes, that's the node we need to keep


					/////////NOTE TO SELF! WAS DOING OPERATIONS ON SELECTEDOBJECT POINTER BEFORE BEING SURE THERE WAS SOMETHING ELSE THAN NULL...
					//ref_ptr made sure the object didn't say null, everything compiles nicely... but no object is there to address at runtime :(
					if(mInput->objectSelected())
						std::cout << "Reference Count: " << mSelectedObjectTrans->referenceCount() << std::endl;
					mSelectedObjectTrans = intersection.nodePath[2]->asTransform()->asMatrixTransform();
					std::cout << "Reference Count: " << mSelectedObjectTrans->referenceCount() << std::endl;

					// Since we might be intersecting the walls/floor of the house
					// We check if this node we are intersecting is actually a selectable

					std::cout << "Object Intersected: " << mSelectedObjectTrans->getName() << std::endl;
					if(mSelectedObjectTrans->getName() == "Model Transformation"){
						// If we are, we want to let the interaction methods about it
						mInput->objectSelected(true);

						// We also need to let them now about the intersected objects whereabouts
						osg::Matrix osg_transf = mSelectedObjectTrans->getMatrix();
						gmtl::Matrix44f  gmtl_transf = convertMatrix(osg_transf);
						//gmtl::Matrix44f  gmtl_transf = convertMatrix(npath[npath.size()-3]->asTransform()->asMatrixTransform()->getMatrix());
						mInput->selectedObjectMatrix(gmtl_transf);
					}
					else {
						// If, while moving the wand, you switch from pointing to the model to pointing a wall...
						mInput->objectSelected(false);
					}
				}
				else{
					// If the user stops intersecting anything
					mInput->objectSelected(false);
				}
			}
			/*

			// Selection and Manipulation can only happen if a ray has been casted by a method
			if(mInput->getRayCasted()){

				// There may be two cases where we don't want to find a new intersection:
				// - We don't have a manipulation method... therefore we may have no need for selected objects
				// - Some manips want to keep the same object that was intersected when the button was first pressed.
				if( mInput->getIntersectionCheck() ){
					// Intersection check
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
						const osgUtil::LineSegmentIntersector::Intersection intersection =
								intersector->getFirstIntersection();

						// We remember our graph structure again
						// mRootNode
						//         \-- mNavTrans -- mModelTrans -- mModel
						//						\-- mHouseTrans -- mHouse
						osg::NodePath npath = intersection.nodePath;
						// The intersection will give us the bottommost node in the graph
						// Although not in our graph representation, the node is actually 
						// a son of mModel, the Mesh.
						// So, in the npath vector, the last element is the mesh. The third
						// to last is the Transformation node we want to modify:
						// -- mModelTrans -- mModel -- MESH   -
						//       size-3      size-2   size-1 size
						mSelectedObjectTrans = npath[npath.size()-3]->asTransform()->asMatrixTransform();

						// Since we might be intersecting the walls/floor of the house
						// We check if this node we are intersecting is actually the model
						if(mSelectedObjectTrans->getName() == "Model Transformation"){
							// If we are, we want to let the interaction methods about it
							mInput->setObjectSelectedFlag(true);

							// We also need to let them now about the intersected objects whereabouts
							osg::Matrix osg_transf = mSelectedObjectTrans->getMatrix();
							gmtl::Matrix44f  gmtl_transf = convertMatrix(osg_transf);
							mInput->setSelectedObjectMatrix(gmtl_transf);
						}
						else {
							// If, while moving the wand, you switch from pointing to the model to pointing a wall...
							mInput->setObjectSelectedFlag(false);
						}
					}
					else{
						// If the user stops intersecting anything
						mInput->setObjectSelectedFlag(false);
					}
				}
				
				// If no button is pressed, there might not be any manipulation to apply
				// Although some manipulations may not need a button to be pressed,
				// also the pressed button number cannot be known from here.
				// The manipulation method needs to let us know if there is any manipulation to do
				if( mInput->getApplyManipulation() ) {
					// We don't try to intersect anything if we already are applying some manipulation

					// Applying just means that we need to convert the matrix that the manip sent
					// and give it to the transformation node that got intersected.
					osg::Matrix osg_transf = convertMatrix( mInput->getSelectedTransformation() );
					if(!osg_transf.isIdentity() && mSelectedObjectTrans->getName() == "Model Transformation" ){
						mSelectedObjectTrans->setMatrix(osg_transf);
						mInput->setSelectedObjectMatrix( mInput->getSelectedTransformation() );
					}
				}
				
			}
			*/
		}

		void SceneRenderer::draw() {
			osg::ref_ptr<osgUtil::SceneView> sv;
			sv = (*sceneViewer);    // Get context specific scene viewer

			if(sv.get() != NULL){
				//sv->setCalcNearFar(false);
				sv->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);

				const int* viewport = mInput->getViewport();
				sv->setViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

				const float* frustum = mInput->getFrustum();
				sv->setProjectionMatrixAsFrustum(frustum[0], frustum[1], frustum[2], frustum[3], frustum[4], frustum[5]);

				sv->setViewMatrix(::osg::Matrix(mInput->getViewMatrix()));

				//Draw the scene
				// NOTE: It is not safe to call osgUtil::SceneView::update() here; it
				// should only be called by a single thread. The equivalent of calling
				// osgUtil::SceneView::update() is in vrj::osg::App::update().
				sv->cull();
				sv->draw();
			}
		}

	}
}
