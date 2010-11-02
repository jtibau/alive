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
#include <alive/interaction/WandDirectionDeltaRotation.h>
#include <alive/interaction/WandDirectionDisplacement.h>
#include <alive/interaction/WandDirectionRay.h>
#include <alive/interaction/PullManipulation.h>

namespace alive {
	namespace interaction {

		/** @addtogroup poly
		  * @{
		  */
	
		/** @class alive::poly::Combination alive/poly/Combination.h
		  * @brief A composition of other provided Interaction Methods
		  *
		  * We can take the code of ready-made methods to combine them into
		  * our preferred interaction.
		  * If a certain combination works for you, it may also be possible
		  * to add it to the default methods.
		  */
		class Combination : public alive::InteractionMethod {

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
			void init(alive::Input* input);

			/** @brief Updates the sub methods
			  */
			void update();
			
		private:
			/** @brief The ray caster method object */
			alive::InteractionMethod *raycast;
			
			/** @brief The scene translation method object */
			alive::InteractionMethod *displacement;
			
			/** @brief The reorientation method object */
			alive::InteractionMethod *rotation;
			
			/** @brief The manipulation method object */
			alive::InteractionMethod *pull;
		};
		/** @} */
	}
}
