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

// These should be changed in favor of platform independent includes
#include <GL/gl.h>
#include <GL/glu.h>

#include "Scene.h"
#include "Input.h"
#include "InteractionMethod.h"

namespace alive {

	/** @class alive::App alive/App.h
	  * @brief The Application class in the library
	  *
	  * It is designed as an interface class, so wrapper classes in the form
	  * of the backends will be able to access the correct methods.
	  *
	  * Most of the times, developers should not need to reimplement this
	  * class. In order to simplify the code, you are encouraged to
	  * provide your Scene and one of the InteractionMethods when
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

		/**	@brief Default constructor
		  *
		  * @note Only use it if you subclass. If not, there is no way to provide
		  * mScene and mInteractionMethod
		  */
		App();

		/** @brief Preferred constructor
		  *
		  *	Provide an uninitialized pointer to your Scene object. The App
		  *	can take a NULL InteractionMethod, if you only want to look at
		  *	the scene and are not interested in interacting with it.
		  */
		App(alive::Scene* scene, alive::InteractionMethod* interactionMethod = NULL);

		virtual ~App();

		/** @brief Application initialization function.
		  *
		  * Execute any initialization needed before the grahpics API is started.
		  * Initializes the members Scene and InteractionMethod
		  */
		virtual void init(alive::Input* input);

		/** @brief Calls mScene->contextInit()
		  */
		virtual void contextInit();

		/** @brief Updates mInteractionMethod
		  */
		virtual void preFrame();

		/** @brief Calls mScene->latePreFrame()
		  */
		virtual void latePreFrame();

		/** @brief Clears the color buffer
		  */
		virtual void bufferPreDraw();

		/** @brief Just before drawing, inside the the opengl context
		  */
		virtual void contextPreDraw();

		/** @brief Draw routine, basically calls mScene->draw()
		  */
		virtual void draw();

		/** @brief Processes that can be performed at the same time as the drawing routine
		  */
		virtual void intraFrame();

		/** @brief After drawing, inside the opengl context
		  */
		virtual void contextPostDraw();

		/** @brief Just before finishing the frame processes
		  */
		virtual void postFrame();

		/** @brief Closing the context, on App exit
		  */
		virtual void contextClose();

		/** @brief Gives mScene the file name of the file to load
		  */
		virtual void setModelName(char* modelFileName);

	protected:

		Scene* mScene;	/**< The object that contains the rendering code */
		Input* mInput;	/**< Input Handler */
		InteractionMethod* mInteractionMethod;	/**< The App's InteractionMethod */
	};
}
