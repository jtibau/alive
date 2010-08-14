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

		virtual double getCurrentTimeStamp() = 0;
		virtual float getTimeDelta() = 0;

		virtual bool getButtonState(unsigned int buttonNumber) = 0;

		virtual gmtl::Vec3f getHeadPosition(Time t = CURRENT) = 0;
		virtual gmtl::Vec3f getHeadDirection(Time t = CURRENT) = 0;
		virtual gmtl::Vec3f getWandPosition(Time t = CURRENT) = 0;
		virtual gmtl::Vec3f getWandDirection(Time t = CURRENT) = 0;

		virtual gmtl::Matrix44f getNavigationMatrix() = 0;
		virtual void setNavigationMatrix(gmtl::Matrix44f navigationMatrix) = 0;

		virtual const int* getViewport() = 0;
		virtual const float* getViewMatrix() = 0;
		virtual const float* getFrustum() = 0;
	};
}
