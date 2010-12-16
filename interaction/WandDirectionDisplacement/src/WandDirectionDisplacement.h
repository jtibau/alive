#pragma once

#include <alice/InteractionMethod.h>
#include <alice/InputHandler.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

#include <gmtl/Generate.h>

namespace alice {
	namespace interaction {
	
		/** @defgroup interaction Default Interaction Methods
		  * @{
		  */
	

		/** @class alice::interaction::WandDirectionDisplacement alice/interaction/WandDirectionDisplacement.h
		  * @brief The most basic navigation type. Move in the direction of the wand.
		  */
		class WandDirectionDisplacement : public alice::InteractionMethod {

		public:
			WandDirectionDisplacement(int buttonNumber = 0) :
					alice::InteractionMethod(buttonNumber)
			{}

			/** @brief Update code, handles what to do with each button press and
			  * changes the navigation matrix according to the method.
			  */
			void update();
		};
		/** @} */
	}
}
