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
		class App : public vrj::opengl::App
		{

		public:
			App(vrj::Kernel* kern, alive::App* app) : vrj::opengl::App(kern) {
				mApp = app;
				mInput = new alive::juggler::Input();
			}
			virtual ~App(){
				delete mApp;
				delete mInput;
			}

		public:
			virtual void init() {
				vrj::opengl::App::init();
				mInput->init();
				mApp->init(mInput);
			}
			virtual void contextInit() { mApp->contextInit(); }

			virtual void preFrame() {
				mInput->update();
				mApp->preFrame();
			}
			virtual void latePreFrame() { mApp->latePreFrame(); }
			virtual void bufferPreDraw() { mApp->bufferPreDraw(); }
			virtual void contextPreDraw() { mApp->contextPreDraw(); }

			virtual void draw() { mApp->draw(); }
			virtual void intraFrame() { mApp->intraFrame(); }

			virtual void contextPostDraw() { mApp->contextPostDraw(); }
			virtual void postFrame() { mApp->postFrame(); }
			virtual void contextClose() { mApp->contextClose(); }

			virtual float getDrawScaleFactor() { return gadget::PositionUnitConversion::ConvertToMeters; }

		private:
			alive::App* mApp;
			alive::Input* mInput;
		};

	}
}
