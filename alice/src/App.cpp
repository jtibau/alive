#include "App.h"

#include <gmtl/VecOps.h>

namespace alice {
	App::App(alice::SceneRenderer* SceneRenderer, alice::InteractionMethod* interactionMethod) {
		mSceneRenderer = SceneRenderer;
		mInteractionMethod = interactionMethod;
	}

	App::~App() {
		if(mSceneRenderer) delete mSceneRenderer;
		if(mInteractionMethod) delete mInteractionMethod;
	}

	void App::init(alice::InputHandler* input) {
		mInput = input;

		if(mSceneRenderer) mSceneRenderer->init(mInput);
		if(mInteractionMethod) mInteractionMethod->init(mInput);
	}

	void App::contextInit() {
		if(mSceneRenderer) mSceneRenderer->contextInit();
	}

	void App::preFrame() {
		if(mInteractionMethod) mInteractionMethod->update();
	}

	void App::latePreFrame() {
		if(mSceneRenderer) mSceneRenderer->latePreFrame();
	}

	void App::bufferPreDraw() {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		if(mSceneRenderer) mSceneRenderer->bufferPreDraw();
	}

	void App::contextPreDraw() {}

	void App::draw() {}

	void App::intraFrame() {}
	void App::contextPostDraw() {}
	void App::postFrame() {}
	void App::contextClose() {}

	InputHandler* App::getInputHandler(){ return mInput; }

	void App::exit(){}
}
