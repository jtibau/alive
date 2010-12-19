#pragma once

#include <alice/InteractionMethod.h>
#include <alice/interaction/Selection/WandDirectionRay.h>
#include <alice/interaction/Navigation/PointingTranslation.h>
#include <alice/interaction/Navigation/HeadWandRotation.h>
#include <alice/interaction/Manipulation/GrabTranslation.h>

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
                displacement = new alice::interaction::PointingTranslation(1);
                rotation = new alice::interaction::HeadWandRotation(2);
                // The ray is always casted, we don't need to press any buttons
                raycast = new alice::interaction::WandDirectionRay();
                // Manipulation happens with the same button we use for interacting with windows
                manipulation = new alice::interaction::GrabTranslation(0);
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
                alice::InteractionMethod::init(input);

                displacement->init(input);
                rotation->init(input);
                raycast->init(input);
                manipulation->init(input);
            }

            /** @brief Updates the sub methods
                */
            void update(){
                displacement->update();
                rotation->update();
                raycast->update();
                manipulation->update();

            }

        private:
            alice::InteractionMethod *raycast;
            alice::InteractionMethod *displacement;
            alice::InteractionMethod *rotation;
            alice::InteractionMethod *manipulation;
        };
        /** @} */
    }
}
