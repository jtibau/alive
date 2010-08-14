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

#include <GL/gl.h>
#include <GL/glu.h>

#include <alive/Scene.h>
#include <alive/Input.h>
#include <alive/InteractionMethod.h>

namespace alive {

	class App {

	public:

		App() {}
		App(alive::Scene* scene, alive::InteractionMethod* interactionMethod) {
			mScene = scene;
			mInteractionMethod = interactionMethod;
		}
		virtual ~App() {}

		virtual void init(alive::Input* input) {
			mInput = input;
			mInput->init();

			mScene->init(mInput);

			if(mInteractionMethod != NULL)
				mInteractionMethod->init(mInput);
		}

		virtual void contextInit() {
			mScene->contextInit();
		}

		virtual void preFrame() {
			if(mInteractionMethod != NULL)
				mInteractionMethod->update();
		}

		virtual void latePreFrame() {
			mScene->latePreFrame();
		}

		virtual void bufferPreDraw() {
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		virtual void contextPreDraw() {}

		virtual void draw() {
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

			mScene->draw();

			glMatrixMode(GL_PROJECTION);
			glPopMatrix();

			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();

			glPopAttrib();
			glPopAttrib();
			glPopAttrib();
		}

		virtual void intraFrame() {}

		virtual void contextPostDraw() {}
		virtual void postFrame() {}
		virtual void contextClose() {}

		virtual void setModelName(char* modelFileName) {
			mScene->setModelName(modelFileName);
		}

	protected:
		Scene* mScene;
		Input* mInput;
		InteractionMethod* mInteractionMethod;
	};
}
