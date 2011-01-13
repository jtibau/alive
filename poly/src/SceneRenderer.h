#pragma once

#include <alice/SceneRenderer.h>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Matrix>
#include <osg/MatrixTransform>

#include <gmtl/Matrix.h>
#include <gmtl/Vec.h>

#include <osgUtil/SceneView>
#include <osgUtil/UpdateVisitor>

#include <osgDB/FileUtils>
#include <fstream>

#include <string>

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

			SceneRenderer(std::string sceneConfigurationFile){
				mFrameNumber = 0;
				osg::Referenced::setThreadSafeReferenceCounting(true);
				mSceneConfigurationFile = sceneConfigurationFile;
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

			gmtl::Matrix44f convertMatrix(osg::Matrix original){
				original.invert(original);
				gmtl::Matrix44f converted;
				converted.set(original(0,0),original(1,0),original(2,0),original(3,0),
				original(0,1),original(1,1),original(2,1),original(3,1),
				original(0,2),original(1,2),original(2,2),original(3,2),
				original(0,3),original(1,3),original(2,3),original(3,3));
				return converted;
			}

			osg::Matrix convertMatrix(gmtl::Matrix44f original){
				osg::Matrix converted(original.getData());
				converted.invert(converted);
				return converted;
			}

			gmtl::Vec3f convertVector(osg::Vec3f original){
				return gmtl::Vec3f(original.x(),original.y(),original.z());
			}
			osg::Vec3f convertVector(gmtl::Vec3f original){
				return osg::Vec3f(original[0],original[1],original[2]);
			}

		protected:

		/** A scene viewer object from osg.
		  * Encapsuled within a ContextData object, a smart pointer which the viewer for each context.
		  */
		vrj::opengl::ContextData< osg::ref_ptr<osgUtil::SceneView> >	sceneViewer;

		osg::ref_ptr< osg::NodeVisitor >								mUpdateVisitor;
		osg::ref_ptr< osg::FrameStamp >  								mFrameStamp;

		int																mFrameNumber;

		/** The root of the scenegraph */
		osg::ref_ptr<osg::Group>           								mRootNode;
		/** A transformation node that affects the position/orientation of the whole scene */
		osg::ref_ptr<osg::MatrixTransform>								mNavTrans;

		/** A pointer to the selected objects transformation, only to be used internally */
		osg::ref_ptr<osg::MatrixTransform>								mSelectedObjectTransformation;

		/** A pointer to the selected objects transformation, used for interactions */
		osg::ref_ptr<osg::Node>											mSelectedObject;

		std::string														mSceneConfigurationFile;
		};
		/** @} */
	}
}
