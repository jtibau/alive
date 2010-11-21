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

#include <alice/InteractionMethod.h>
#include <alice/interaction/WandDirectionDeltaRotation.h>
#include <alice/interaction/WandDirectionDisplacement.h>
#include <alice/interaction/WandDirectionRay.h>
#include <alice/interaction/PullManipulation.h>

namespace alice {
	namespace interaction {

		/** @addtogroup poly
		  * @{
		  */
	
		/** @class alice::poly::Combination alice/poly/Combination.h
		  * @brief A composition of other provided Interaction Methods
		  *
		  * We can take the code of ready-made methods to combine them into
		  * our preferred interaction.
		  * If a certain combination works for you, it may also be possible
		  * to add it to the default methods.
		  */
		class Combination : public alice::InteractionMethod {

		public:
			/** @brief Instantiates the sub methods
			  *
			  * Tells each sub method which button to use. It might not
			  * really use the buttonNumber parametter... It's up to you.
			  */
			Combination(int buttonNumber = 0);

			/** @brief Destroy sub methods
			  */
			~Combination();

			/** @brief Store input and init sub methods
			  */
			void init(alice::InputHandler* input);

			/** @brief Updates the sub methods
			  */
			void update();
			
		private:
			/** @brief The ray caster method object */
			alice::InteractionMethod *raycast;
			
			/** @brief The scene translation method object */
			alice::InteractionMethod *displacement;
			
			/** @brief The reorientation method object */
			alice::InteractionMethod *rotation;
			
			/** @brief The manipulation method object */
			alice::InteractionMethod *pull;
		};
		/** @} */
	}
}
