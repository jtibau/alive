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

#include <vrj/vrjConfig.h>

#include <vrj/Draw/OpenGL/App.h>
#include <vrj/Kernel/Kernel.h>

#include <alive/App.h>
#include "Input.h"

namespace alive{
	namespace juggler{

		/** @class alive::juggler::App alive/juggler/App
		  * @brief Wrapper class to interface between VR Juggler and our alive::App
		  *
		  * This class takes an alive::App object and calls its methods at the correct places.
		  * It also provides the alive::App object with an juggler implementation of Input.
		  */
		class App : public vrj::opengl::App{

		public:

			/** @brief Constructor
			  *
			  * Gives the vrjuggler kernel to the parent class.
			  * Keeps the app pointer and instantiates a concrete implementation
			  * of the Input class that deals with the vrjuggler framework.
			  */
			App(vrj::Kernel* kern, alive::App* app);

			/** @brief Destructor
			  *
			  * Since this class instantiates Input, this class also sends the destroy signal.
			  */
			virtual ~App();

			/** @brief Initialization code
			  *
			  * Calls vrjuggler's vrj::opengl::App init method.
			  * Inits the Input object and gives it to mApp.
			  */
			virtual void init();

			/** @brief Calls alive::App's contextInit
			  */
			virtual void contextInit();

			/** @brief Updates the Input object, calls alive::App's preFrame
			  */
			virtual void preFrame();

			/** @brief Calls alive::App's latePreFrame
			  */
			virtual void latePreFrame();

			/** @brief Calls alive::App's bufferPreDraw
			  */
			virtual void bufferPreDraw();

			/** @brief Calls alive::App's contextPreDraw
			  */
			virtual void contextPreDraw();

			/** @brief Calls alive::App's draw
			  */
			virtual void draw();

			/** @brief Calls alive::App's intraFrame
			  */
			virtual void intraFrame();

			/** @brief Calls alive::App's contextPostDraw
			  */
			virtual void contextPostDraw();

			/** @brief Calls alive::App's postFrame
			  */
			virtual void postFrame();

			/** @brief Calls alive::App's contextClose
			  */
			virtual void contextClose();

			/** @brief Returns the scale factor, in order to convert to the
			  * spacially correct unit.
			  */
			virtual float getDrawScaleFactor();

		private:
			alive::App* mApp; /**< Pointer to the user's App */
			alive::Input* mInput; /**< Pointer to a juggler Input object */
		};
	}
}
