#pragma once

#include <vrj/vrjConfig.h>

#include <alice/InputHandler.h>

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

			/** @brief Initializes the devices according to VR Juggler requirements */
			void init();

			/** @brief Updates device state */
			void update();

			/** @brief Returns the OpenGL context */
			unsigned int getCurrentContext();

			/** @brief Locks the mutex */
			void lockMutex();

			/** @brief Releases the mutex lock */
			void releaseMutex();

			/** @brief Returns the OpenGL Viewport */
			const int* getViewport();

			/** @brief Returns the OpenGL View Matrix */
			const float* getViewMatrix();

			/** @brief Returns the OpenGL Frustum */
			const float* getFrustum();

		private:

			gadget::PositionInterface  mWand;							/**< The VRJuggler pointer to the Wand */
			gadget::PositionInterface  mHead;							/**< The VRJuggler pointer to the Head */
			gadget::DigitalInterface   mButtonInterface[MAX_BUTTONS];	/**< The VRJuggler pointers to the buttons */

			bool mFirstButtonClick[MAX_BUTTONS];						/**< A hack, to handle a current bug with the VRPN driver in vrj SS*/

			vpr::Guard<vpr::Mutex> *mGuard;								/**< Used to handle VR Juggler's mutex objects */
			vpr::Mutex mLock;											/**< VR Juggler's mutex lock object */
		};
		/** @} */
	}
}
