#pragma once

#include <alice/InteractionMethod.h>

namespace alice {
	namespace interaction {
		/** @addtogroup interaction
		  * @{
		  */

		/** @class alice::interaction::HandBasicManipulation alice/interaction/HandBasicManipulation.h
		  * @brief Moves the selected object according to the wand's movement
		  *
		  */
		class HandBasicManipulation : public alice::InteractionMethod {

		public:

			/** @brief Constructor, calls parent and stores the button number
			  */
			HandBasicManipulation(int buttonNumber = 0);

			/** @brief Destructor
			  */
			~HandBasicManipulation();

			void init(alice::InputHandler *input);

			/** @brief Moves the selected object according to the wand's movement
			  *
			  */
			void update();
		};
		/** @} */
	}
}
