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

namespace alive {
	namespace interaction {

		/** @class alive::interaction::BasicNavigation alive/interaction/BasicNavgigation.h
		  * @brief A very basic reorientation type.
		  * 
		  * Rotates to the angle formed between the delta formed by moving the wand around the head
		  */
		class WandDirectionDeltaRotation : public alive::InteractionMethod {

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
	}
}
