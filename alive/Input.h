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

#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>

#define MAX_BUTTONS 3

namespace alive {

	class Scene;

	enum Time {
		CURRENT, PREVIOUS
	};

	class Input {

	public:

		Input() {}
		virtual ~Input() {};

		virtual void init() = 0;
		virtual void update() = 0;

		virtual unsigned int getCurrentContext() = 0;

		virtual double getCurrentTimeStamp(){
			return mCurrentTime;
		}

		virtual float getTimeDelta(){
			return mTimeDelta;
		}

		virtual bool getButtonState(unsigned int buttonNumber) {
			if(buttonNumber < MAX_BUTTONS)
				return mButtonState[buttonNumber];
			else return false;
		}

		virtual gmtl::Vec3f getHeadPosition(Time t = CURRENT) {
			if(t == PREVIOUS) return mPreviousHeadPosition;
			return mHeadPosition;
		}
		virtual gmtl::Vec3f getHeadDirection(Time t = CURRENT) {
			if(t == PREVIOUS) return mPreviousHeadDirection;
			return mHeadDirection;
		}
		virtual gmtl::Vec3f getWandPosition(Time t = CURRENT) {
			if(t == PREVIOUS) return mPreviousWandPosition;
			return mWandPosition;
		}
		virtual gmtl::Vec3f getWandDirection(Time t = CURRENT) {
			if(t == PREVIOUS) return mPreviousWandDirection;
			return mWandDirection;
		}

		virtual gmtl::Matrix44f getNavigationMatrix(){
			return mNavigationMatrix;
		}
		virtual void setNavigationMatrix(gmtl::Matrix44f navigationMatrix){
			mNavigationMatrix = navigationMatrix;
		}

		virtual const int* getViewport() = 0;
		virtual const float* getViewMatrix() = 0;
		virtual const float* getFrustum() = 0;

	protected:
		gmtl::Vec3f mHeadPosition, mHeadDirection;
		gmtl::Vec3f mPreviousHeadPosition, mPreviousHeadDirection;
		gmtl::Vec3f mWandPosition, mWandDirection;
		gmtl::Vec3f mPreviousWandPosition, mPreviousWandDirection;

		bool mButtonState[MAX_BUTTONS];

		double mCurrentTime, mPreviousTime;
		float mTimeDelta;

		gmtl::Matrix44f mNavigationMatrix;
	};
}
