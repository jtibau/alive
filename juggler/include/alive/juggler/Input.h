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

#include <alive/Input.h>
#include <alive/Scene.h>

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

namespace alive {
	namespace juggler {

		/** @class alive::juggler::Input alive/juggler/Input.h
		  * @brief VR Juggler implementation of the abstract alive::Input
		  *
		  * @note alive::Input (father) is better documented, read it.
		  */
		class Input : public alive::Input {

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
		};
	}
}
