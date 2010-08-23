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
#include <alive/juggler/Input.h>

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
			  */
			App(vrj::Kernel* kern, alive::App* app) : vrj::opengl::App(kern) {
				mApp = app;
				mInput = new alive::juggler::Input();
			}

			/** @brief Destructor
			  *
			  * Since this class instantiates Input, this class also sends the destroy signal.
			  */
			virtual ~App(){
				delete mApp;
				delete mInput;
			}

			/** @brief Initialization code
			  *
			  * Calls vrjuggler's vrj::opengl::App init method.
			  * Inits the Input object and gives it to mApp.
			  */
			virtual void init() {
				vrj::opengl::App::init();
				mInput->init();
				mApp->init(mInput);
			}

			/** @brief Calls alive::App's contextInit
			  */
			virtual void contextInit() { mApp->contextInit(); }

			/** @brief Updates the Input object, calls alive::App's preFrame
			  */
			virtual void preFrame() {
				mInput->update();
				mApp->preFrame();
			}

			/** @brief Calls alive::App's latePreFrame
			  */
			virtual void latePreFrame() { mApp->latePreFrame(); }

			/** @brief Calls alive::App's bufferPreDraw
			  */
			virtual void bufferPreDraw() { mApp->bufferPreDraw(); }

			/** @brief Calls alive::App's contextPreDraw
			  */
			virtual void contextPreDraw() { mApp->contextPreDraw(); }

			/** @brief Calls alive::App's draw
			  */
			virtual void draw() { mApp->draw(); }

			/** @brief Calls alive::App's intraFrame
			  */
			virtual void intraFrame() { mApp->intraFrame(); }

			/** @brief Calls alive::App's contextPostDraw
			  */
			virtual void contextPostDraw() { mApp->contextPostDraw(); }

			/** @brief Calls alive::App's postFrame
			  */
			virtual void postFrame() { mApp->postFrame(); }

			/** @brief Calls alive::App's contextClose
			  */
			virtual void contextClose() { mApp->contextClose(); }

			/** @brief Returns the scale factor, in order to convert to the spacially correct unit.
			  */
			virtual float getDrawScaleFactor() { return gadget::PositionUnitConversion::ConvertToMeters; }

		private:
			alive::App* mApp; /**< Pointer to the user's App */
			alive::Input* mInput; /**< Pointer to a juggler Input object */
		};
	}
}
