#include <alive/juggler/App.h>

namespace alive {
	namespace juggler {
		App::App(vrj::Kernel* kern, alive::App* app)
			: vrj::opengl::App(kern) {
			mApp = app;
			mInput = new alive::juggler::Input();
		}

		App::~App(){
			delete mApp;
			delete mInput;
		}

		void App::init() {
			vrj::opengl::App::init();
			mInput->init();
			mApp->init(mInput);
		}

		void App::contextInit() { mApp->contextInit(); }

		void App::preFrame() {
			mInput->update();
			mApp->preFrame();
		}

		void App::latePreFrame() { mApp->latePreFrame(); }

		void App::bufferPreDraw() { mApp->bufferPreDraw(); }

		void App::contextPreDraw() { mApp->contextPreDraw(); }

		void App::draw() { mApp->draw(); }

		void App::intraFrame() { mApp->intraFrame(); }

		void App::contextPostDraw() { mApp->contextPostDraw(); }

		void App::postFrame() { mApp->postFrame(); }

		void App::contextClose() { mApp->contextClose(); }

		float App::getDrawScaleFactor() { return gadget::PositionUnitConversion::ConvertToMeters; }

	}
}
