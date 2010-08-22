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

#pragma once

#include <osg/Group>
#include <osg/Geode>
#include <osg/MatrixTransform>

#include <osgUtil/SceneView>
#include <osgUtil/UpdateVisitor>

#include <vrj/Draw/OpenGL/ContextData.h>

#include <alive/Scene.h>

namespace alive {

	class Input;

	namespace poly {

		class Scene : public alive::Scene {

		public:

			Scene() : mFrameNumber(0) {
				osg::Referenced::setThreadSafeReferenceCounting(true);
			}

			void init(Input* input);
			void contextInit();

			void latePreFrame();
			void draw();

			void navigationMatrixChanged(const float* navigationMatrix);

		protected:

			vrj::opengl::ContextData< ::osg::ref_ptr<osgUtil::SceneView> > sceneViewer;
			vpr::Mutex mSceneViewLock;

			osg::ref_ptr< osg::NodeVisitor > mUpdateVisitor;
			osg::ref_ptr< osg::FrameStamp >  mFrameStamp;

			osg::ref_ptr<osg::Group>           mRootNode;
			osg::ref_ptr<osg::MatrixTransform> mNavTrans;
			osg::ref_ptr<osg::MatrixTransform> mModelTrans;
			osg::ref_ptr<osg::Node>            mModel;

			int mFrameNumber;
		};

	}

}
