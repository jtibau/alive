#include "InputHandler.h"

#include <iostream>

namespace alice {
	namespace juggler {
		void InputHandler::init(){
			mWand.init("VJWand");
			mHead.init("VJHead");
			for(int i=0; i<MAX_BUTTONS; i++){
				std::stringstream buttonName;
				buttonName << "VJButton" << i;
				mButtonInterface[i].init(buttonName.str());
				mButtonState[i] = false;
				mButtonChanged[i] = false;
				mFirstButtonClick[i] = true;
			}
			mCurrentTime = 0;
			mObjectSelectedFlag = false;
		}

		void InputHandler::update(){
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
			gmtl::Matrix44f wandMatrix = mWand->getData(gadget::PositionUnitConversion::ConvertToMeters);
			gmtl::xform(mWandDirection, wandMatrix, Zdir);
			mWandPosition = gmtl::makeTrans<gmtl::Point3f>(wandMatrix);

			// update head data
			gmtl::Matrix44f headMatrix = mHead->getData(gadget::PositionUnitConversion::ConvertToMeters);
			gmtl::xform(mHeadDirection, headMatrix, Zdir);
			mHeadPosition = gmtl::makeTrans<gmtl::Point3f>(headMatrix);

			// update button data only if the digital interface reports a toggle
			for(int i=0; i<MAX_BUTTONS; i++){
				if(!mFirstButtonClick[i]){
					mButtonChanged[i] = false;
					if( mButtonInterface[i]->getData() == gadget::Digital::TOGGLE_ON )
						mButtonChanged[i] = mButtonState[i] = true;
					if( mButtonInterface[i]->getData() == gadget::Digital::TOGGLE_OFF )
						mButtonChanged[i] = !(mButtonState[i] = false);	// ;)
				}
				else if( mButtonInterface[i]->getData() == gadget::Digital::TOGGLE_OFF )
					mFirstButtonClick[i] = false;
			}
		}

		unsigned int InputHandler::getCurrentContext(){
			return vrj::opengl::DrawManager::instance()->getCurrentContext();
		}

		void InputHandler::lockMutex(){
			mGuard = new vpr::Guard<vpr::Mutex>(mLock);
		}

		void InputHandler::releaseMutex(){
			delete mGuard;
		}

		const int* InputHandler::getViewport(){
			vrj::opengl::DrawManager* gl_manager = vrj::opengl::DrawManager::instance();

			vprASSERT(gl_manager != NULL);

			vrj::opengl::UserData* user_data = gl_manager->currentUserData();

			float vp_ox, vp_oy, vp_sx, vp_sy;   // The float vrj sizes of the view ports
			int w_ox, w_oy, w_width, w_height;  // Origin and size of the window
			user_data->getViewport()->getOriginAndSize(vp_ox, vp_oy, vp_sx, vp_sy);
			user_data->getGlWindow()->getOriginSize(w_ox, w_oy, w_width, w_height);

			// compute unsigned versions of the viewport info (for passing to glViewport)
			int* v = new int[4];
			v[0] = static_cast<int>(vp_ox * static_cast<float>(w_width));
			v[1] = static_cast<int>(vp_oy * static_cast<float>(w_height));
			v[2] = static_cast<int>(vp_sx * static_cast<float>(w_width));
			v[3] = static_cast<int>(vp_sy * static_cast<float>(w_height));

			return v;
		}

		const float* InputHandler::getViewMatrix(){
			vrj::opengl::DrawManager* gl_manager = vrj::opengl::DrawManager::instance();
			vprASSERT(gl_manager != NULL);
			vrj::opengl::UserData* user_data = gl_manager->currentUserData();

			vrj::ProjectionPtr project = user_data->getProjection();
			return project->getViewMatrix().mData;
		}

		const float* InputHandler::getFrustum(){
			vrj::opengl::DrawManager* gl_manager = vrj::opengl::DrawManager::instance();
			vprASSERT(gl_manager != NULL);
			vrj::opengl::UserData* user_data = gl_manager->currentUserData();

			vrj::ProjectionPtr project = user_data->getProjection();
			vrj::Frustum frustum = project->getFrustum();

			float* f = new float[6];
			f[0] = frustum[vrj::Frustum::VJ_LEFT];
			f[1] = frustum[vrj::Frustum::VJ_RIGHT];
			f[2] = frustum[vrj::Frustum::VJ_BOTTOM];
			f[3] = frustum[vrj::Frustum::VJ_TOP];
			f[4] = frustum[vrj::Frustum::VJ_NEAR];
			f[5] = frustum[vrj::Frustum::VJ_FAR];

			return f;
		}
	}
}
