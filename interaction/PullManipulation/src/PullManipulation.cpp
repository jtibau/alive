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

#include "PullManipulation.h"

#include <gmtl/VecOps.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Xforms.h>

namespace alive{
	namespace interaction{
		void PullManipulation::update(){
			if( mInput->getButtonState(mButtonNumber) && mInput->getObjectSelectedFlag() ){
					gmtl::Matrix44f objectMatrix = mInput->getSelectedObjectMatrix();
					gmtl::Matrix44f nav = mInput->getNavigationMatrix();

					gmtl::Vec3f translation =  mInput->getWandDirection();
					translation = nav * translation;
					translation *= 4 * mInput->getTimeDelta();	// move faster/slower
					translation[1] = 0.0f;	// comment out if you wanna fly!
					// Post multiply the delta translation
					gmtl::Matrix44f trans_matrix = objectMatrix * gmtl::makeTrans<gmtl::Matrix44f>(translation);

					mInput->setSelectedTransformation(trans_matrix);
					mInput->setApplyManipulation(true);
				}	
		}
	}
}
