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

#include "HeadToWandRay.h"

#include <alice/InputHandler.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace alice{
	namespace interaction{
		HeadToWandRay::HeadToWandRay(int buttonNumber) :
			alice::InteractionMethod(buttonNumber)
		{}

		HeadToWandRay::~HeadToWandRay(){}

		void HeadToWandRay::update(){
			mInput->setRayStart( mInput->getHeadPosition() );
			mInput->setRayEnd( mInput->getWandPosition() );
		}
	}
}

