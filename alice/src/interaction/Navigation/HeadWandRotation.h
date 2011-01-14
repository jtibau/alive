#pragma once

#include <alice/InteractionMethod.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

namespace alice {
	namespace interaction {

		/** @addtogroup interaction
			* @{
			*/

		/** @class alice::interaction::HeadWandRotation alice/interaction/Navigation/HeadWandRotation.h
			* @brief A very basic reorientation type.
			*
			* Rotates to the angle formed between the delta formed by moving the wand around the head
			*/
		class HeadWandRotation : public alice::InteractionMethod {

		public:
			/** @brief Constructor */
			HeadWandRotation(int buttonNumber = 0) :
					alice::InteractionMethod(buttonNumber)
			{}


			/** @brief Rotates the user's viewpoint	*/
			void update(){
				// lot of math on these transformations
				if( mInput->getButtonState(mButtonNumber) ){
					// Both vectors go from the head's to the wand's position
					gmtl::Vec3f v1 = mInput->getWandPosition(alice::PREVIOUS) - mInput->getHeadPosition(alice::PREVIOUS);
					gmtl::Vec3f v2 = mInput->getWandPosition() - mInput->getHeadPosition();

					// Don't do anything if the wand/head haven't moved at all
					if( v1!= v2 ){
						// In order to do any calculations with them, we first need unit vectors
						gmtl::normalize(v1);
						gmtl::normalize(v2);

						gmtl::Vec3f v3,v4;
						gmtl::cross(v3,v1,v2);
						gmtl::normalize(v3);
						gmtl::cross(v4,v3,v1);
						gmtl::normalize(v4);

						// the rotation factors for the rotation matrix
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

						float x_rot = 0;//(gmtl::makeRot<gmtl::EulerAngleXYZf>(transfMat))[0];
						float y_rot = (gmtl::makeRot<gmtl::EulerAngleXYZf>(transfMat))[1];
						float z_rot = 0; // (gmtl::makeRot<gmtl::EulerAngleXYZf>(transfMat))[2];

						gmtl::Matrix44f navigationMatrix = mInput->navigationMatrix();

						gmtl::postMult(navigationMatrix, gmtl::makeTrans<gmtl::Matrix44f>(mInput->getHeadPosition()));
						gmtl::postMult(navigationMatrix, gmtl::makeRot<gmtl::Matrix44f>(gmtl::EulerAngleXYZf(x_rot,y_rot,z_rot)));
						gmtl::postMult(navigationMatrix, gmtl::makeTrans<gmtl::Matrix44f>(-mInput->getHeadPosition()));

						mInput->navigationMatrix(navigationMatrix);
						mInput->applyNavigation(true);
					}
				}
			}
		};
		/** @} */
	}
}
