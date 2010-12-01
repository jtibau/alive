#include "Combination.h"

namespace alice {
	namespace interaction {
		Combination::Combination(int buttonNumber){
			// My combination of interaction methods:
			// First button moves in the direction of the wand
                        displacement = new alice::interaction::WandDirectionDisplacement(2);
			// Third button reorientates the navigation
			rotation = new alice::interaction::WandDirectionDeltaRotation(2);
			// The ray is always casted, we don't need to press any buttons
			raycast = new alice::interaction::WandDirectionRay();
			
			manipulation = new alice::interaction::HandBasicManipulation(1);
		}

		Combination::~Combination(){
			delete displacement;
			delete raycast;
			delete rotation;
			delete manipulation;
		}

		void Combination::init(alice::InputHandler* input){
			// The individual methods don't need to overide this method
			// When initing call the parent method (or just store the input in mInput
			alice::InteractionMethod::init(input);
			// And the sub methods also need input of course
			displacement->init(input);
			rotation->init(input);
			raycast->init(input);
			manipulation->init(input);
		}
		void Combination::update(){
			// have everything update
			displacement->update();
			rotation->update();
			raycast->update();
			manipulation->update();
		}
	}
}
