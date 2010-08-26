#include <alive/App.h>

namespace alive {
	App::App(){}

	App::App(alive::Scene* scene, alive::InteractionMethod* interactionMethod) {
		mScene = scene;
		mInteractionMethod = interactionMethod;
	}

	App::~App() {}

	void App::init(alive::Input* input) {
		mInput = input;

		if(mScene) mScene->init(mInput);
		if(mInteractionMethod) mInteractionMethod->init(mInput);
	}

	void App::contextInit() {
		if(mScene) mScene->contextInit();
	}

	void App::preFrame() {
		if(mInteractionMethod) mInteractionMethod->update();
	}

	void App::latePreFrame() {
		if(mScene) mScene->latePreFrame();
	}

	void App::bufferPreDraw() {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		if(mScene) mScene->bufferPreDraw();
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

		if(mScene) mScene->draw();


		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();


		// Drawing the Wand
		glDisable(GL_LIGHTING);
		glColor3f(0.663f,0.83f,0.51f);
		glLineWidth(1.);

		glBegin(GL_LINES);
		{
			gmtl::Vec3f start = mInput->getRayStart();
			gmtl::Vec3f end = mInput->getRayEnd();
			glVertex3f(start[0],start[1],start[2]);
			glVertex3f(end[0],end[1],end[2]);
		}
		glEnd();

		glEnable(GL_LIGHTING);
		// Wand Drawn

		glPopAttrib();
		glPopAttrib();
		glPopAttrib();
	}

	void App::intraFrame() {}
	void App::contextPostDraw() {}
	void App::postFrame() {}
	void App::contextClose() {}

	void App::setModelName(char* modelFileName) {
		if(mScene) mScene->setModelName(modelFileName);
	}
}
