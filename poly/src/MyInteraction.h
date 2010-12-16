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
#include <alice/interaction/HandBasicManipulation.h>
#include <alice/interaction/WandDirectionRay.h>
#include <alice/interaction/HeadToWandRay.h>

namespace alice {
    namespace poly{
        /** @addtogroup poly
              * @{
              */

        /** @class alice::poly::MyInteraction alice/poly/MyInteraction.h
              * @brief A composition of other provided Interaction Methods
              *
              * We can take the code of ready-made methods to combine them into
              * our preferred interaction.
              * If a certain combination works for you, it may also be possible
              * to add it to the default methods.
              */
        class MyInteraction : public alice::InteractionMethod {

        public:
            /** @brief Instantiates the sub methods
                *
                * Tells each sub method which button to use. It might not
                * really use the buttonNumber parametter... It's up to you.
                */
            MyInteraction(){
                // Two methods for navigating the scene
                // First button moves in the direction of the wand
                displacement = new alice::interaction::WandDirectionDisplacement(1);
                // Third button reorientates the navigation
                rotation = new alice::interaction::WandDirectionDeltaRotation(2);

                // The ray is always casted, we don't need to press any buttons
                raycast = new alice::interaction::WandDirectionRay();
                //raycast = new alice::interaction::HeadToWandRay();

                // Manipulation happens with the same button we use for interacting with windows
                manipulation = new alice::interaction::HandBasicManipulation(0);
            }

            /** @brief Destroy sub methods
                */
            ~MyInteraction(){
                delete displacement;
                delete raycast;
                delete rotation;
                delete manipulation;
            }

            /** @brief Store input and init sub methods
                */
            void init(alice::InputHandler* input){
                // The individual methods don't need to overide this method
                // When initing call the parent method (or just store the input in mInput
                alice::InteractionMethod::init(input);
                // And the sub methods also need input of course
                displacement->init(input);
                rotation->init(input);
                raycast->init(input);
                manipulation->init(input);
            }

            /** @brief Updates the sub methods
                */
            void update(){
                // have everything update
                displacement->update();
                rotation->update();
                raycast->update();
                manipulation->update();

            }

        private:
            /** @brief The ray caster method object */
            alice::InteractionMethod *raycast;

            /** @brief The scene translation method object */
            alice::InteractionMethod *displacement;

            /** @brief The reorientation method object */
            alice::InteractionMethod *rotation;

            alice::InteractionMethod *manipulation;
        };
        /** @} */

    }
}
