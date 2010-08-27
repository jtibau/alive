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

#include <iostream>

namespace alive {
	namespace interaction {

		/** @class alive::interaction::WandDirectionRay alive/interaction/WandDirectionRay.h
		  * @brief A very basic ray casting technique.
		  *
		  * Sets the casted ray to be in the direction of the wand
		  */
		class WandDirectionRay : public alive::InteractionMethod {

		public:

			/** @brief Constructor, calls parent
			  */
			WandDirectionRay(int buttonNumber = 0);

			~WandDirectionRay();

			/** @brief Update code, for selection methods it means to set the casted ray's start and end vectors
			  */
			void update();
		};
	}
}
