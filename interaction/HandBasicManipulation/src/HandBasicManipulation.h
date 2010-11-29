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
