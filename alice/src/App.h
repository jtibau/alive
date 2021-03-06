#pragma once

// These should be changed in favor of platform independent includes
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneRenderer.h"
#include "InputHandler.h"
#include "InteractionMethod.h"

namespace alice {

	/** @defgroup alice ALICE Abstract Classes
	  * @{
	  */
	  
	/** @class alice::App alice/App.h
	  * @brief The Application class in the library
	  *
	  * It is designed as an interface class, so wrapper classes in the form
	  * of the backends will be able to access the correct methods.
	  *
	  * Most of the times, developers should not need to reimplement this
	  * class. In order to simplify the code, you are encouraged to
	  * provide your SceneRenderer and one of the InteractionMethods when
	  * instantiating your App.
	  *
	  * The control loop of the application will be similar to this:
	  * \code
	  * app_obj->contextInit();        // called for each context
	  * while (drawing)
	  * {
	  *    app_obj->preFrame();
	  *    app_obj->latePreFrame();
	  *    app_obj->bufferPreDraw();   // called for each draw buffer
	  *    app_obj->contextPreDraw();  // called for each context
	  *    app_obj->draw();            // called for each viewport
	  *    app_obj->contextPostDraw(); // called for each context
	  *    app_obj->intraFrame();      // called in parallel to the draw functions
	  *    sync();
	  *    app_obj->postFrame();
	  *
	  *    updateAllDevices();
	  * }
	  * app_obj->contextClose();       // called for each context
	  * \endcode
	  *
	  * @note The interface is a clone of vrj::opengl::App
	  */
	class App {

	public:

		/** @brief Preferred constructor
		  *
		  *	Provide an uninitialized pointer to your SceneRenderer object. The App
		  *	can take a NULL InteractionMethod, if you only want to look at
		  *	the SceneRenderer and are not interested in interacting with it.
		  */
		App(alice::SceneRenderer* SceneRenderer = NULL,
			alice::InteractionMethod* interactionMethod = NULL);
		
		/** @brief Destructor
		  *
		  * Should delete the SceneRenderer and InteractionMethod
		  */
		virtual ~App();

		/** @brief Application initialization function.
		  *
		  * Execute any initialization needed before the grahpics API is started.
		  * Initializes the members SceneRenderer and InteractionMethod
		  */
		virtual void init(alice::InputHandler* input);

		/** @brief Calls mSceneRenderer->contextInit()
		  */
		virtual void contextInit();

		/** @brief Updates mInteractionMethod
		  */
		virtual void preFrame();

		/** @brief Calls mSceneRenderer->latePreFrame()
		  */
		virtual void latePreFrame();

		/** @brief Clears the color buffer
		  */
		virtual void bufferPreDraw();

		/** @brief Just before drawing, inside the the opengl context
		  */
		virtual void contextPreDraw();

		/** @brief Draw routine, basically calls mSceneRenderer->draw()
		  */
		virtual void draw();

		/** @brief Processes that can be performed at the same time
		  *  as the drawing routine
		  */
		virtual void intraFrame();

		/** @brief After drawing, inside the opengl context
		  */
		virtual void contextPostDraw();

		/** @brief Just before finishing the Exitframe processes
		  */
		virtual void postFrame();

		/** @brief Closes the context, on App exit.
		  */
		virtual void contextClose();
		
		/** @brief Exits the application.
		  */
		virtual void exit();

		/** @brief Grants access to the application's InputHandler object.
		  */
		virtual InputHandler* getInputHandler();
		
	protected:

		InputHandler*		mInput;			/**< Input Handler */
		SceneRenderer*		mSceneRenderer;		/**< The object that contains the rendering code */
		InteractionMethod*	mInteractionMethod;	/**< The App's InteractionMethod */
	};
	/** @} */
}
