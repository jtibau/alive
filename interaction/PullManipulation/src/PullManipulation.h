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

		/** @class alice::interaction::PullManipulation alice/interaction/PullManipulation.h
		  * @brief Pulls the selected object towards the wand
		  */
		class PullManipulation : public alice::InteractionMethod {

		public:
			/** @brief Constructor
			  */
			PullManipulation(int buttonNumber = 0) :
				alice::InteractionMethod(buttonNumber)
			{}

			/** @brief inits the method
			  *
			  * Tells the scene that it should be checking intersections and
			  * calls the parent init.
			  */
			void init(alice::InputHandler* input);

			/** @brief Update code, handles what to do with each button press and
			  * changes the navigation matrix according to the method.
			  */
			void update();
		};
		/** @} */
	}
}
