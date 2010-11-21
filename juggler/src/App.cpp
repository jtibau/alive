#include "App.h"

#include <iostream>

namespace alice {
	namespace juggler {
		App::App(vrj::Kernel* kern, alice::App* app)
			: vrj::opengl::App(kern) {
			mApp = app;
			mInput = new alice::juggler::InputHandler();
		}

		App::~App(){
		  std::cout << "Deleting the juggler app\n";
			if(mApp) delete mApp;
			delete mInput;
		}

		void App::init() {
			vrj::opengl::App::init();
			mInput->init();
			if(mApp) mApp->init(mInput);
		}

		void App::contextInit() { if(mApp) mApp->contextInit(); }

		void App::preFrame() {
			mInput->update();
			if(mApp) mApp->preFrame();
		}

		void App::latePreFrame() { if(mApp) mApp->latePreFrame(); }

		void App::bufferPreDraw() { if(mApp) mApp->bufferPreDraw(); }

		void App::contextPreDraw() { if(mApp) mApp->contextPreDraw(); }

		void App::draw() { if(mApp) mApp->draw(); }

		void App::intraFrame() { if(mApp) mApp->intraFrame(); }

		void App::contextPostDraw() { if(mApp) mApp->contextPostDraw(); }

		void App::postFrame() { if(mApp) mApp->postFrame(); }

		void App::contextClose() { if(mApp) mApp->contextClose(); }
		
		void App::exit() { if(mApp) mApp->exit(); }

		float App::getDrawScaleFactor() { return gadget::PositionUnitConversion::ConvertToMeters; }

	}
}
