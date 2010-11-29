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
		class HeadToWandRay : public alice::InteractionMethod {

		public:

			/** @brief Constructor, calls parent and stores the button number
			  */
			HeadToWandRay(int buttonNumber = 0);

			/** @brief Destructor
			  */
			~HeadToWandRay();

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
