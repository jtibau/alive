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

#include <alice/SceneRenderer.h>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Matrix>
#include <osg/MatrixTransform>

#include <osgUtil/SceneView>
#include <osgUtil/UpdateVisitor>

#include <osgDB/FileUtils>
#include <fstream>

#include <vrj/Draw/OpenGL/ContextData.h>

namespace alice {

  class InputHandler;

  namespace poly {

		/** @defgroup poly Polygon Renderer
		  * @{
		  */

		/** @class alice::poly::SceneRenderer alice/poly/SceneRenderer.h
		  * @brief Sample Implementation of the alice::SceneRenderer class
		  *
		  * This SceneRenderer and package (poly) implements alice.
		  * It is a *simple* polygonal renderer based on openscenegraph
		  *
		  * @note Two features will be deprecated from this implementation,
		  * since they make this code vrj-dependant: vpr::Mutex and
		  * vrj::opengl::ContextData. They should be replaced by wrapper
		  * objects in alice.
		  */
		class SceneRenderer : public alice::SceneRenderer {

		public:

			/** @brief Default Constructor
			  *
			  * Sets mFrameNumber to 0 and configures threading on osg
			  */
			SceneRenderer() : mFrameNumber(0) {
				osg::Referenced::setThreadSafeReferenceCounting(true);
			}

			/** @brief Initializes the SceneRenderer
			  *
			  * Creates the structure for the graph and loads the model.
			  * @note It is possible that model loading (if not modularized) be better done in contextInit
			  */
			void init(InputHandler* input);

			/** @brief Initializes context specific variables and objects.
			  *
			  * Which in this case is the helper class osgUtil::SceneView
			  */
			void contextInit();

			/** @brief Updates to the SceneRenderer
			  *
			  * Updates the scene by:
			  * - Increasing the frame number
			  * - Giving it the current timestamp
			  * - Updates the NodeVisitor mUdateVisitor
			  * - Tells the scene to calculate the newer bounding boxes
			  *
			  * @note It also gets the most recent navigation matrix from InputHandler, this should be replaced by signals and slots
			  */
			void latePreFrame();

			void bufferPreDraw(){}

			/** @brief Rendering code, made context-specific through ContextData
			  *
			  * Gets the sceneViewer object for the current context. Gives it the current
			  * viewport, frustum and view matrix. Tells osg to do some culling and send the draw commands.
			  */
			void draw();

			//Convertion methods

		protected:

			/** A scene viewer object from osg.
			  * Encapsuled within a ContextData object, a smart pointer which the viewer for each context.
			  */
			vrj::opengl::ContextData< osg::ref_ptr<osgUtil::SceneView> > sceneViewer;

			osg::ref_ptr< osg::NodeVisitor > mUpdateVisitor;
			osg::ref_ptr< osg::FrameStamp >  mFrameStamp;

			int mFrameNumber;

			/** Used for handling shaders and uniforms */
			osg::StateSet   *rootStateSet;
			osg::Program    *programObject;
			osg::Shader     *vertexObject;
			osg::Shader     *fragmentObject;

			// mRootNode -- mNavTrans -- mModelTrans -- mModel
			//					             \-- mHouseTrans -- mHouse
			osg::ref_ptr<osg::Group>           mRootNode;     /**< The root of the scenegraph */
			osg::ref_ptr<osg::MatrixTransform> mNavTrans;     /**< A transformation node that affects the position/orientation of the whole scene */
			osg::ref_ptr<osg::MatrixTransform> mModelTrans;   /**< Transformation specific to the loaded model */
			osg::ref_ptr<osg::Node>            mModel;        /**< The node where the model is loaded and placed */
			osg::ref_ptr<osg::MatrixTransform> mHouseTrans;		/**< Transformation specific to the world model */
			osg::ref_ptr<osg::Node>            mHouse;				/**< The node where the world/house model is loaded */

			/** A pointer to the selected objects transformation, only to be used internally */
			osg::ref_ptr<osg::MatrixTransform> mSelectedObjectTransformation;
		};
		/** @} */
	}
}
