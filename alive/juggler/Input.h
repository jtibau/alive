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
		  */
		class Input : public alive::Input {

		public:

			/** @brief Initializes the devices according to VR Juggler requirements
			  */
			void init(){
				mWand.init("VJWand");
				mHead.init("VJHead");
				for(int i=0; i<MAX_BUTTONS; i++){
					std::stringstream buttonName;
					buttonName << "VJButton" << i;
					mButtonInterface[i].init(buttonName.str());
					mButtonState[i] = false;
					mFirstButtonClick[i] = true;
				}
				mCurrentTime = 0;
			}

			/** @brief Updates device state
			  */
			void update(){
				mPreviousTime = mCurrentTime;
				mCurrentTime = mHead->getTimeStamp().secd();
				mTimeDelta = (float)(mCurrentTime - mPreviousTime);


				// store previous head and wand data
				mPreviousWandPosition = mWandPosition;
				mPreviousWandDirection = mWandDirection;
				mPreviousHeadPosition = mHeadPosition;
				mPreviousHeadDirection = mHeadDirection;

				// forward vector
				gmtl::Vec3f Zdir = gmtl::Vec3f(0.0f, 0.0f, -1.0f);

				// update wand data
				gmtl::Matrix44f wandMatrix = mWand->getData();
				gmtl::xform(mWandDirection, wandMatrix, Zdir);
				mWandPosition = gmtl::makeTrans<gmtl::Point3f>(wandMatrix);

				// update head data
				gmtl::Matrix44f headMatrix = mHead->getData();
				gmtl::xform(mHeadDirection, headMatrix, Zdir);
				mHeadPosition = gmtl::makeTrans<gmtl::Point3f>(headMatrix);

				// update button data only if the digital interface reports a toggle
				for(int i=0; i<MAX_BUTTONS; i++){
					if(!mFirstButtonClick[i]){
						if( mButtonInterface[i]->getData() == gadget::Digital::TOGGLE_ON )
							mButtonState[i] = true;
						if( mButtonInterface[i]->getData() == gadget::Digital::TOGGLE_OFF )
							mButtonState[i] = false;
					}
					else{
						if( mButtonInterface[i]->getData() == gadget::Digital::TOGGLE_OFF ) mFirstButtonClick[i] = false;
					}
				}
			}

			/** @brief Returns the OpenGL context
			  */
			unsigned int getCurrentContext(){
				return vrj::opengl::DrawManager::instance()->getCurrentContext();
			}

			/** @brief Returns the OpenGL Viewport
			  */
			const int* getViewport(){
				vrj::opengl::DrawManager* gl_manager = vrj::opengl::DrawManager::instance();
				vprASSERT(gl_manager != NULL);
				vrj::opengl::UserData* user_data = gl_manager->currentUserData();

				float vp_ox, vp_oy, vp_sx, vp_sy;   // The float vrj sizes of the view ports
				int w_ox, w_oy, w_width, w_height;  // Origin and size of the window
				user_data->getViewport()->getOriginAndSize(vp_ox, vp_oy, vp_sx, vp_sy);
				user_data->getGlWindow()->getOriginSize(w_ox, w_oy, w_width, w_height);

				// compute unsigned versions of the viewport info (for passing to glViewport)
				int v[4];
				v[0] = static_cast<int>(vp_ox * static_cast<float>(w_width));
				v[1] = static_cast<int>(vp_oy * static_cast<float>(w_height));
				v[2] = static_cast<int>(vp_sx * static_cast<float>(w_width));
				v[3] = static_cast<int>(vp_sy * static_cast<float>(w_height));

				return v;
			}

			/** @brief Returns the OpenGL View Matrix
			  */
			const float* getViewMatrix(){
				vrj::opengl::DrawManager* gl_manager = vrj::opengl::DrawManager::instance();
				vprASSERT(gl_manager != NULL);
				vrj::opengl::UserData* user_data = gl_manager->currentUserData();

				vrj::ProjectionPtr project = user_data->getProjection();
				return project->getViewMatrix().mData;
			}

			/** @brief Returns the OpenGL Frustum
			  */
			const float* getFrustum(){
				vrj::opengl::DrawManager* gl_manager = vrj::opengl::DrawManager::instance();
				vprASSERT(gl_manager != NULL);
				vrj::opengl::UserData* user_data = gl_manager->currentUserData();

				vrj::ProjectionPtr project = user_data->getProjection();
				vrj::Frustum frustum = project->getFrustum();

				float f[6];
				f[0] = frustum[vrj::Frustum::VJ_LEFT];
				f[1] = frustum[vrj::Frustum::VJ_RIGHT];
				f[2] = frustum[vrj::Frustum::VJ_BOTTOM];
				f[3] = frustum[vrj::Frustum::VJ_TOP];
				f[4] = frustum[vrj::Frustum::VJ_NEAR];
				f[5] = frustum[vrj::Frustum::VJ_FAR];

				return f;
			}

		private:

			gadget::PositionInterface  mWand; /**< The VRJuggler pointer to the Wand */
			gadget::PositionInterface  mHead; /**< The VRJuggler pointer to the Head */
			gadget::DigitalInterface   mButtonInterface[MAX_BUTTONS]; /**< The VRJuggler pointers to the buttons */

			bool mFirstButtonClick[MAX_BUTTONS]; /**< A hack, to handle a current bug with the VRPN driver in vrj*/
		};
	}
}
