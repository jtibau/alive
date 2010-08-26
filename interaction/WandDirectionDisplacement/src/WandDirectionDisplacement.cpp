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

#include "WandDirectionDisplacement.h"

namespace alive{
	namespace interaction{
		void WandDirectionDisplacement::update(){
			// Translate in the direction the wand is pointing.
			if ( mInput->getButtonState(mButtonNumber) ){
				gmtl::Matrix44f navigationMatrix = mInput->getNavigationMatrix();
				gmtl::Vec3f translation =  mInput->getWandDirection() * mInput->getTimeDelta();
				translation *= 3;	// move faster/slower
				translation[1] = 0.0f;	// comment out if you wanna fly!
				// Post multiply the delta translation
				gmtl::Matrix44f trans_matrix = gmtl::makeTrans<gmtl::Matrix44f>(translation);

				gmtl::postMult(navigationMatrix, trans_matrix);
				mInput->setNavigationMatrix(navigationMatrix);
			}		
		}
	}
}
