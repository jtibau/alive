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

#include <alive/InteractionMethod.h>
#include <alive/Input.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

#include <gmtl/Generate.h>

#include <iostream>

namespace alive {
	namespace interaction {

		/** @class alive::interaction::BasicRayIntersection alive/interaction/BasicRayIntersection.h
		  * @brief A very basic ray casting technique.
		  *
		  * Casts a ray and sends the signal to the scene... for now it just means that it
		  * will keep alive::Input updated in regards of the pos/rot/size of the ray
		  */
		class BasicRayIntersection : public alive::InteractionMethod {

		public:

			/** @brief Update code, handles what to do with each button press and changes the ray pos/dir/size
			  */
			void update(){
				gmtl::Vec3f start = mInput->getWandPosition();
				gmtl::Vec3f dir = mInput->getWandDirection() *2.0f;
				gmtl::Vec3f end = start + dir;

				mInput->setRayStart( start );
				mInput->setRayEnd( end );

				// This is actually manip code
				if( mInput->getButtonState(0) && mInput->getObjectSelectedFlag() ){
					std::cout << "Sending new matrix\n";
					gmtl::Matrix44f objectMatrix = mInput->getSelectedObjectMatrix();
					gmtl::Vec3f translation =  mInput->getWandDirection() * mInput->getTimeDelta();
					// translation *= 1;	// move faster/slower
					translation[1] = 0.0f;	// comment out if you wanna fly!
					// Post multiply the delta translation
					gmtl::Matrix44f trans_matrix = objectMatrix * gmtl::makeTrans<gmtl::Matrix44f>(translation);

					mInput->setSelectedTransformation(trans_matrix);
				}
			}
		};
	}
}
