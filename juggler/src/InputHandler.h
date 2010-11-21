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

#include <alice/InputHandler.h>
//#include <alice/SceneRenderer.h>

#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/DigitalInterface.h>

#include <gmtl/Generate.h>
#include <gmtl/VecOps.h>
#include <gmtl/MatrixOps.h>

#include <vrj/Draw/OpenGL/Window.h>
#include <vrj/Draw/OpenGL/DrawManager.h>
#include <vrj/Display/CameraProjection.h>
#include <vrj/Kernel/User.h>

#include <iostream>

namespace alice {
	namespace juggler {

		/** @addtogroup juggler
		  * @{
		  */
	
		/** @class alice::juggler::InputHandler alice/juggler/InputHandler.h
		  * @brief VR Juggler implementation of the abstract alice::InputHandler
		  *
		  * @note alice::InputHandler (father) is better documented, read it.
		  */
		class InputHandler : public alice::InputHandler {

		public:

			/** @brief Initializes the devices according to VR Juggler requirements
			  */
			void init();

			/** @brief Updates device state
			  */
			void update();

			/** @brief Returns the OpenGL context
			  */
			unsigned int getCurrentContext();

			void lockMutex();
			void releaseMutex();

			/** @brief Returns the OpenGL Viewport
			  */
			const int* getViewport();

			/** @brief Returns the OpenGL View Matrix
			  */
			const float* getViewMatrix();

			/** @brief Returns the OpenGL Frustum
			  */
			const float* getFrustum();

		private:

			gadget::PositionInterface  mWand; /**< The VRJuggler pointer to the Wand */
			gadget::PositionInterface  mHead; /**< The VRJuggler pointer to the Head */
			gadget::DigitalInterface   mButtonInterface[MAX_BUTTONS]; /**< The VRJuggler pointers to the buttons */

			bool mFirstButtonClick[MAX_BUTTONS]; /**< A hack, to handle a current bug with the VRPN driver in vrj SS*/

			vpr::Guard<vpr::Mutex> *mGuard;
			vpr::Mutex mLock;
		};
		/** @} */
	}
}
