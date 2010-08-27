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

#include "WandDirectionRay.h"

namespace alive{
	namespace interaction{
		WandDirectionRay::WandDirectionRay(int buttonNumber) :
			alive::InteractionMethod(buttonNumber)
		{}

		WandDirectionRay::~WandDirectionRay(){}

		void WandDirectionRay::update(){
			gmtl::Vec3f start = mInput->getWandPosition();
			gmtl::Vec3f dir = mInput->getWandDirection() *2.0f;
			gmtl::Vec3f end = start + dir;

			mInput->setRayStart( start );
			mInput->setRayEnd( end );
			
			mInput->setRayCasted(true);
		}
	}
}

