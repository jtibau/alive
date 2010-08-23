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


		/** @class alive::poly::Scene alive/poly/Scene.h
		  * @brief Sample Implementation of the alive::Scene class
		  *
		  * This and package implement ALIVE, as a simple polygonal renderer based on openscenegraph
		  *
		  * @note Two features will be deprecated from this implementation, since they make this code
		  * vrj-dependant: vpr::Mutex and vrj::opengl::ContextData. They should be replaced by wrapper
		  * objects in ALIVE.
		  */
		class Scene : public alive::Scene {

		public:

			/** @brief Default Constructor
			  *
			  * Sets mFrameNumber to 0 and configures threading on osg
			  */
			Scene() : mFrameNumber(0) {
				osg::Referenced::setThreadSafeReferenceCounting(true);
			}

			/** @brief Initializes the SceneGraph
			  *
			  * Creates the structure for the graph and loads the model.
			  * @note It is possible that model loading (if not modularized) be better done in contextInit
			  */
			void init(Input* input);

			/** @brief Initializes context specific variables and objects.
			  *
			  * Which in this case is the helper class osgUtil::SceneView
			  */
			void contextInit();

			/** @brief Updates to the Scene
			  *
			  * Updates the scene by:
			  * - Increasing the frame number
			  * - Giving it the current timestamp
			  * - Updates the NodeVisitor mUdateVisitor
			  * - Tells the scene to calculate the newer bounding boxes
			  *
			  * @note It also gets the most recent navigation matrix from Input, this should be replaced by signals and slots
			  */
			void latePreFrame();

			/** @brief Rendering code, made context-specific through ContextData
			  *
			  * Gets the sceneViewer object for the current context. Gives it the current
			  * viewport, frustum and view matrix. Tells osg to do some culling and send the draw commands.
			  */
			void draw();

			/** @brief Updates the navigation matrix for this Scene
			  *
			  * Replaces the old navigation matrix with the one provided
			  */
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
