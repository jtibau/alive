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

			//
			// mRootNode
			//         \-- mNavTrans -- mModelTrans -- mModel

			//The top level nodes of the tree
			mRootNode = new osg::Group();
			mNavTrans = new osg::MatrixTransform();

			mRootNode->addChild(mNavTrans.get());

			//Load the model
			std::cout << "Attempting to load file: " << mFileToLoad << "... ";
			mModel = osgDB::readNodeFile(mFileToLoad);
			std::cout << "done." << std::endl;

			// Transform node for the model
			mModelTrans  = new osg::MatrixTransform();
			//This can be used if the model orientation needs to change
			//mModelTrans->preMult(osg::Matrix::rotate(-90.0, osg::Vec3f(1.0,0.0,0.0)));
			mModelTrans->preMult(osg::Matrix::translate(osg::Vec3f(-2.0,0.0,-2.0)));
			mModelTrans->setName("Model Transformation");

			if ( ! mModel.valid() )
				std::cout << "ERROR: Could not load file: " << mFileToLoad << std::endl;
			else
				mModelTrans->addChild(mModel.get());

			// Add the transform to the tree
			mNavTrans->addChild(mModelTrans.get());
		}

		void Scene::contextInit(){
			const unsigned int unique_context_id = mInput->getCurrentContext();
			//vrj::opengl::DrawManager::instance()->getCurrentContext();

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
				newSceneViewer->setClearColor(::osg::Vec4(0.0f, 0.0f, 0.0f, 0.0f));

				// Needed for stereo to work.
				newSceneViewer->setDrawBufferValue(GL_NONE);

				newSceneViewer->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
				newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
				newSceneViewer->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
			}

			new_sv->getState()->setContextID(unique_context_id);

			// Add the tree to the scene viewer and set properties
			{
				vpr::Guard<vpr::Mutex> sv_guard(mSceneViewLock);
				new_sv->setSceneData(mRootNode.get());
			}

			(*sceneViewer) = new_sv;
		}

		void Scene::latePreFrame(){
			navigationMatrixChanged(mInput->getNavigationMatrix().getData());

			const double head_time = mInput->getCurrentTimeStamp();
			++mFrameNumber;

			// Update the frame stamp with information from this frame.
			mFrameStamp->setFrameNumber(mFrameNumber);
			mFrameStamp->setReferenceTime(head_time);
			mFrameStamp->setSimulationTime(head_time);

			mUpdateVisitor->setTraversalNumber(mFrameNumber);
			mRootNode.get()->accept(*mUpdateVisitor);
			mRootNode.get()->getBound();

			// Intersection check
			gmtl::Vec3f s = mInput->getRayStart();
			gmtl::Vec3f e = mInput->getRayEnd();
			osg::Vec3d start(s[0],s[1],s[2]);
			osg::Vec3d end(e[0],e[1],e[2]);
			osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
					new osgUtil::LineSegmentIntersector(start, end);
			osgUtil::IntersectionVisitor intersectVisitor( intersector.get() );
			mRootNode->accept(intersectVisitor);

			if(intersector->containsIntersections()){
				const osgUtil::LineSegmentIntersector::Intersection intersection =
						intersector->getFirstIntersection();

				osg::NodePath npath = intersection.nodePath;
				osg::ref_ptr<osg::MatrixTransform> intersectedNode =
						npath[npath.size()-3]->asTransform()->asMatrixTransform();
				//std::cout << "Intersected: " << intersectedNode->getName() << std::endl;
				mInput->setObjectSelectedFlag(true);

				osg::Matrixf transf = intersectedNode->getMatrix();
				transf.invert(transf);

				float tmatrix[4][4];
				for(int i; i<4; i++)
					for(int j; j<4; j++)
						tmatrix[i][j] = transf(i,j);
				gmtl::Matrix44f tm;

				// find a way to convert from osg::Matrix to float* without doing the above
				//tm.set(transf._mat);

				mInput->setSelectedTransformation(tm);
			}
			else{ mInput->setObjectSelectedFlag(false); }
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

		void Scene::navigationMatrixChanged(const float* navigationMatrix){
			osg::Matrix nav;
			nav.set(navigationMatrix);
			nav.invert(nav);

			mNavTrans->setMatrix(nav);
		}
	}
}
