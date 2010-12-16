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

	void App::draw() {
		glClear(GL_DEPTH_BUFFER_BIT);

		// Users have reported problems with OpenGL reporting stack underflow
		// problems when the texture attribute bit is pushed here, so we push all
		// attributes *except* GL_TEXTURE_BIT.
		glPushAttrib(GL_ALL_ATTRIB_BITS & ~GL_TEXTURE_BIT);
		glPushAttrib(GL_TRANSFORM_BIT);
		glPushAttrib(GL_VIEWPORT_BIT);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		if(mSceneRenderer) mSceneRenderer->draw();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glPopAttrib();
		glPopAttrib();
		glPopAttrib();
	}

	void App::intraFrame() {}
	void App::contextPostDraw() {}
	void App::postFrame() {}
	void App::contextClose() {}

  void App::exit(){}
}
