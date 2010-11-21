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

/*
		// Drawing the Wand
		glDisable(GL_LIGHTING);
		glColor3f(0.663f,0.83f,0.51f);
		glLineWidth(1.);

		glBegin(GL_LINES);
		{
			gmtl::Vec3f start = mInput->getWandPosition();
			gmtl::Vec3f end = mInput->getWandPosition();
			end += mInput->getWandDirection();

			glVertex3f(start[0],start[1],start[2]);
			glVertex3f(end[0],end[1],end[2]);
		}
		glEnd();

		glEnable(GL_LIGHTING);
		// Wand Drawn
*/
		glPopAttrib();
		glPopAttrib();
		glPopAttrib();
	}

	void App::intraFrame() {}
	void App::contextPostDraw() {}
	void App::postFrame() {}
	void App::contextClose() {}

  void App::exit(){}
  
	void App::setModelName(char* modelFileName) {
		if(mSceneRenderer) mSceneRenderer->setModelName(modelFileName);
	}
}
