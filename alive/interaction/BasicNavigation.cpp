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

#include "BasicNavigation.h"

#include <iostream>

namespace alive{
	namespace interaction{
		void BasicNavigation::update(){
			gmtl::Matrix44f navigationMatrix = mInput->getNavigationMatrix();

			// Translate in the direction the wand is pointing.
			if ( mInput->getButtonState(0) ){
				gmtl::Vec3f translation =  mInput->getWandDirection() * mInput->getTimeDelta();
				// translation *= 1;	// move faster/slower
				translation[1] = 0.0f;	// comment out if you wanna fly!
				// Post multiply the delta translation
				gmtl::Matrix44f trans_matrix = gmtl::makeTrans<gmtl::Matrix44f>(translation);

				gmtl::postMult(navigationMatrix, trans_matrix);
			}
			if( mInput->getButtonState(1) )
			{
				gmtl::Vec3f v1,v2;

				v1 = mInput->getWandPosition(alive::PREVIOUS) - mInput->getHeadPosition(alive::PREVIOUS);
				v2 = mInput->getWandPosition() - mInput->getHeadPosition();

				if(v1!=v2){
					gmtl::normalize(v1);
					gmtl::normalize(v2);

					gmtl::Vec3f v3,v4;

					gmtl::cross(v3,v1,v2);
					gmtl::normalize(v3);
					gmtl::cross(v4,v3,v1);
					gmtl::normalize(v4);

					float u = gmtl::dot(v2,v1);
					float v = gmtl::dot(v2,v4);

					gmtl::Matrix44f m1, im1, m2;

					m1.set(v1[0],v1[1],v1[2],0,
						   v4[0],v4[1],v4[2],0,
						   v3[0],v3[1],v3[2],0,
						   0,0,0,1);
					m2.set(u,v,0,0,
						   -v,u,0,0,
						   0,0,1,0,
						   0,0,0,1);

					im1 = m1;
					gmtl::invert(im1);

					gmtl::Matrix44f transfMat = im1 * m2 * m1;


					float x_rot = 0;
					float y_rot = 0;
					float z_rot = 0;

					//x_rot = (gmtl::makeRot<gmtl::EulerAngleXYZf>(transfMat))[0];
					y_rot = (gmtl::makeRot<gmtl::EulerAngleXYZf>(transfMat))[1];
					//z_rot = (gmtl::makeRot<gmtl::EulerAngleXYZf>(transfMat))[2];

					std::cout << "Head position: x" << mInput->getHeadPosition()[0]
							<< " y" << mInput->getHeadPosition()[1]
							<< " z" << mInput->getHeadPosition()[2]
							<< std::endl;

					gmtl::postMult(navigationMatrix, gmtl::makeTrans<gmtl::Matrix44f>(mInput->getHeadPosition()));
					gmtl::postMult(navigationMatrix, gmtl::makeRot<gmtl::Matrix44f>(gmtl::EulerAngleXYZf(x_rot,y_rot,z_rot)));
					gmtl::postMult(navigationMatrix, gmtl::makeTrans<gmtl::Matrix44f>(-mInput->getHeadPosition()));

				}
			}
			mInput->setNavigationMatrix(navigationMatrix);
		}
	}
}
