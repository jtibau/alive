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
#include <alive/Input.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

#include <gmtl/Generate.h>

namespace alive {
	namespace interaction {
	
		/** @defgroup interaction Default Interaction Methods
		  * @{
		  */
	

		/** @class alive::interaction::WandDirectionDisplacement alive/interaction/WandDirectionDisplacement.h
		  * @brief The most basic navigation type. Move in the direction of the wand.
		  */
		class WandDirectionDisplacement : public alive::InteractionMethod {

		public:
			WandDirectionDisplacement(int buttonNumber = 0) :
					alive::InteractionMethod(buttonNumber)
			{}

			/** @brief Update code, handles what to do with each button press and
			  * changes the navigation matrix according to the method.
			  */
			void update();
		};
		/** @} */
	}
}
