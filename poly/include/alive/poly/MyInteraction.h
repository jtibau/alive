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


namespace alive {
	namespace poly {

		class MyInteraction : public alive::InteractionMethod {

		public:
			MyInteraction(int buttonNumber = 0){
				displacement = new alive::interaction::WandDirectionDisplacement(0);
				//rotation = new alive::interaction::WandDirectionDeltaRotation(2);
			}

			~MyInteraction(){
				delete displacement;
				//delete rotation;
			}
			
			void init(alive::Input* input){
				alive::InteractionMethod::init(input);
				displacement->init(input);
			}

			void update();
		private:
			alive::InteractionMethod *displacement;
			alive::InteractionMethod *rotation;
		};
	}
}
