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

#include "Scene.h"

#include <osgDB/ReadFile>
#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>

#include <iostream>

#include <alive/Input.h>

namespace alive {

	namespace poly {

		void Scene::init(Input* input){
			alive::Scene::init(input);

			mUpdateVisitor = new osgUtil::UpdateVisitor();
			mFrameStamp    = new ::osg::FrameStamp();
			mUpdateVisitor->setFrameStamp(mFrameStamp.get());

			mRootNode = new osg::Group();
			mNavTrans = new osg::MatrixTransform();
			mRootNode->addChild(mNavTrans.get());

			mModel = osgDB::readNodeFile("./data/stand.3DS");
			mModelTrans  = new osg::MatrixTransform();
			mModelTrans->setName("Model Transformation");
			mModelTrans->preMult(osg::Matrix::translate(osg::Vec3f(-2.0,0.0,-2.0)));
			mModelTrans->addChild(mModel.get());
			mNavTrans->addChild(mModelTrans.get());

			mHouse = osgDB::readNodeFile("./data/casa.3DS");
			mHouseTrans = new osg::MatrixTransform();
			mHouseTrans->addChild(mHouse.get());
			mNavTrans->addChild(mHouseTrans.get());
		}

		void Scene::contextInit(){
			const unsigned int unique_context_id = mInput->getCurrentContext();

			// --- Create new context specific scene viewer -- //
			::osg::ref_ptr<osgUtil::SceneView> new_sv(new osgUtil::SceneView);

			{
				osgUtil::SceneView* newSceneViewer = new_sv.get();
				newSceneViewer->setDefaults(osgUtil::SceneView::STANDARD_SETTINGS);

				// Set the timing information in the scene view. This has to be done
				// only once per osgUtil::SceneView instance and should be done before
				// calling osgUtil::SceneView::init().
				newSceneViewer->setFrameStamp(mFrameStamp.get());

				newSceneViewer->init();
				//135-206-250
				newSceneViewer->setClearColor(::osg::Vec4(135.0f/256.0f, 206.0f/256.0f, 250.0f/256.0f, 1.0f));

				// Needed for stereo to work.
				newSceneViewer->setDrawBufferValue(GL_NONE);

				newSceneViewer->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
				newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
				newSceneViewer->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));

				newSceneViewer->getLight()->setPosition(osg::Vec4(0.0f,5.0f,0.0f,1.0f));
			}

			new_sv->getState()->setContextID(unique_context_id);

			// Add the tree to the scene viewer and set properties
			{
				vpr::Guard<vpr::Mutex> sv_guard(mSceneViewLock);
				new_sv->setSceneData(mRootNode.get());
			}

			(*sceneViewer) = new_sv;
		}

		gmtl::Matrix44f convertMatrix(osg::Matrix original){
			original.invert(original);
			gmtl::Matrix44f converted;
			converted.set(original(0,0),original(1,0),original(2,0),original(3,0),
						  original(0,1),original(1,1),original(2,1),original(3,1),
						  original(0,2),original(1,2),original(2,2),original(3,2),
						  original(0,3),original(1,3),original(2,3),original(3,3));

			return converted;
		}

		osg::Matrix converMatrix(gmtl::Matrix44f original){
			osg::Matrix converted(original.getData());
			converted.invert(converted);
			return converted;
		}


		void Scene::latePreFrame(){
			navigationMatrixChanged(mInput->getNavigationMatrix());

			const double head_time = mInput->getCurrentTimeStamp();
			++mFrameNumber;

			// Update the frame stamp with information from this frame.
			mFrameStamp->setFrameNumber(mFrameNumber);
			mFrameStamp->setReferenceTime(head_time);
			mFrameStamp->setSimulationTime(head_time);

			mUpdateVisitor->setTraversalNumber(mFrameNumber);
			mRootNode.get()->accept(*mUpdateVisitor);
			mRootNode.get()->getBound();


			if(mInput->getRayCasted()){

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
				if(intersector->containsIntersections()){
					const osgUtil::LineSegmentIntersector::Intersection intersection =
							intersector->getFirstIntersection();

					osg::NodePath npath = intersection.nodePath;
					osg::ref_ptr<osg::MatrixTransform> intersectedNode =
							npath[npath.size()-3]->asTransform()->asMatrixTransform();

					if(intersectedNode->getName() == "Model Transformation"){
						mInput->setObjectSelectedFlag(true);

						osg::Matrix osg_transf = intersectedNode->getMatrix();
						gmtl::Matrix44f  gmtl_transf = convertMatrix(osg_transf);
						mInput->setSelectedObjectMatrix(gmtl_transf);

						// Apply manipulation
						if( mInput->getApplyManipulation() ){
							osg_transf = converMatrix( mInput->getSelectedTransformation() );
							if(!osg_transf.isIdentity()) intersectedNode->setMatrix(osg_transf);
						}
					}
				}
				else{ mInput->setObjectSelectedFlag(false); }
			}



		}

		void Scene::draw() {
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

		void Scene::navigationMatrixChanged(gmtl::Matrix44f navigationMatrix){
			osg::Matrix nav;
			nav.set(navigationMatrix.getData());
			nav.invert(nav);

			mNavTrans->setMatrix(nav);
		}
	}
}
