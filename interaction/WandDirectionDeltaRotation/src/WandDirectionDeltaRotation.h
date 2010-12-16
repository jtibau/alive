#pragma once

#include <alice/InteractionMethod.h>

namespace alice {
	namespace interaction {

		/** @addtogroup interaction
		  * @{
		  */
	
		/** @class alice::interaction::WandDirectionDeltaRotation alice/interaction/WandDirectionDeltaRotation.h
		  * @brief A very basic reorientation type.
		  * 
		  * Rotates to the angle formed between the delta formed by moving the wand around the head
		  */
		class WandDirectionDeltaRotation : public alice::InteractionMethod {

		public:
			/** @brief Constructor
			  */
			WandDirectionDeltaRotation(int buttonNumber = 0);


			/** @brief Update code, handles what to do when the button is pressed
			  *
			  * Changes the navigation matrix according to the method.
			  */
			void update();
		};
		/** @} */
	}
}
