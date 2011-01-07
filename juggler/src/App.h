#pragma once

#include <vrj/vrjConfig.h>

#include <vrj/Draw/OpenGL/App.h>
#include <vrj/Kernel/Kernel.h>

#include <alice/App.h>
#include "InputHandler.h"

namespace alice{
	namespace juggler{
	
		/** @defgroup juggler VR Juggler Backend
		  * @{
		  */
	
		/** @class alice::juggler::App alice/juggler/App
		  * @brief Wrapper class to interface between VR Juggler and our alice::App
		  *
		  * This class takes an alice::App object and calls its methods at the correct places.
		  * It also provides the alice::App object with an juggler implementation of InputHandler.
		  */
		class App : public vrj::opengl::App{

		public:

			/** @brief Constructor
			  *
			  * Gives the vrjuggler kernel to the parent class.
			  * Keeps the app pointer and instantiates a concrete implementation
			  * of the InputHandler class that deals with the vrjuggler framework.
			  */
			App(vrj::Kernel* kern, alice::App* app);

			/** @brief Destructor
			  *
			  * Since this class instantiates InputHandler, this class also sends the destroy signal.
			  */
			virtual ~App();

			/** @brief Initialization code
			  *
			  * Calls vrjuggler's vrj::opengl::App init method.
			  * Inits the InputHandler object and gives it to mApp.
			  */
			virtual void init();

			/** @brief Calls alice::App's contextInit */
			virtual void contextInit();

			/** @brief Updates the InputHandler object, calls alice::App's preFrame */
			virtual void preFrame();

			/** @brief Calls alice::App's latePreFrame */
			virtual void latePreFrame();

			/** @brief Calls alice::App's bufferPreDraw */
			virtual void bufferPreDraw();

			/** @brief Calls alice::App's contextPreDraw */
			virtual void contextPreDraw();

			/** @brief Calls alice::App's draw */
			virtual void draw();

			/** @brief Calls alice::App's intraFrame */
			virtual void intraFrame();

			/** @brief Calls alice::App's contextPostDraw */
			virtual void contextPostDraw();

			/** @brief Calls alice::App's postFrame */
			virtual void postFrame();

			/** @brief Calls alice::App's contextClose */
			virtual void contextClose();
			
			virtual void exit();

			/** @brief Returns the scale factor, in order to convert to the
			  * spacially correct unit.
			  */
			virtual float getDrawScaleFactor();

		private:
			alice::App* mApp;				/**< Pointer to the user's App */
			alice::InputHandler* mInput;	/**< Pointer to a juggler InputHandler object */
		};
		/** @} */
	}
}
