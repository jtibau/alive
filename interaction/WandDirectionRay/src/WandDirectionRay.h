#pragma once

#include <alice/InteractionMethod.h>

namespace alice {
	namespace interaction {
		/** @addtogroup interaction
		  * @{
		  */

		/** @class alice::interaction::WandDirectionRay alice/interaction/WandDirectionRay.h
		  * @brief A very basic ray casting technique.
		  *
		  * Sets the casted ray to be in the direction of the wand
		  */
		class WandDirectionRay : public alice::InteractionMethod {

		public:

			/** @brief Constructor, calls parent and stores the button number
			  */
			WandDirectionRay(int buttonNumber = 0);

			/** @brief Destructor
			  */
			~WandDirectionRay();

			/** @brief Sets the casted ray's start and end vectors
			  *
			  * This method's ray starts at the wand position and stretches in the
			  * direction of the wand by 4 meters.
			  */
			void update();
		};
		/** @} */
	}
}
