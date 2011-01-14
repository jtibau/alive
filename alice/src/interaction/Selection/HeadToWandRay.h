#pragma once

#include <alice/InteractionMethod.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace alice {
	namespace interaction {
		/** @addtogroup interaction
			* @{
			*/

		/** @class alice::interaction::HeadToWandRay alice/interaction/HeadToWandRay.h
			* @brief A very basic ray casting technique.
			*
			* Sets the casted ray to start at the head and point towards the wand.
			*/
		class HeadToWandRay : public alice::InteractionMethod {

		public:

			/** @brief Constructor, calls parent and stores the button number
				*/
			HeadToWandRay(int buttonNumber = 0) :
					alice::InteractionMethod(buttonNumber)
			{}

			/** @brief Destructor
				*/
			~HeadToWandRay(){}

			/** @brief Sets the casted ray's start and end vectors
				*
				* This method's ray starts at the wand position and stretches in the
				* direction of the wand by 4 meters.
				*/
			void update(){
				mInput->setRayStart( mInput->getHeadPosition() );
				gmtl::Vec3f direction = mInput->getWandPosition() - mInput->getHeadPosition();
				direction *= 4;
				mInput->setRayEnd( mInput->getHeadPosition() + direction );
			}
		};
		/** @} */
	}
}
