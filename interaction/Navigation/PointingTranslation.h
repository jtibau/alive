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

		/** @defgroup interaction Default Interaction Methods
			* @{
			*/


		/** @class alice::interaction::PointingTranslation alice/interaction/Navigation/PointingTranslation.h
			* @brief The most basic navigation type. Move in the direction of the wand.
			*/
		class PointingTranslation : public alice::InteractionMethod {

		public:
			PointingTranslation(int buttonNumber = 0) :
					alice::InteractionMethod(buttonNumber)
			{}

			/** @brief Update code, handles what to do with each button press and
				* changes the navigation matrix according to the method.
				*/
			void update(){
				// Translate in the direction the wand is pointing.
				if ( mInput->getButtonState(mButtonNumber) ){
					gmtl::Matrix44f navigationMatrix = mInput->navigationMatrix();
					gmtl::Vec3f translation =  mInput->getWandDirection() * mInput->getTimeDelta();
					translation *= 3;	// move faster/slower
					//translation[1] = 0.0f;	// comment out if you wanna fly!
					// Post multiply the delta translation
					gmtl::Matrix44f trans_matrix = gmtl::makeTrans<gmtl::Matrix44f>(translation);

					gmtl::postMult(navigationMatrix, trans_matrix);
					mInput->navigationMatrix(navigationMatrix);
					mInput->applyNavigation(true);
				}
			}
		};
		/** @} */
	}
}
