#include "MyInteraction.h"

namespace alive {
	namespace poly {
		MyInteraction::MyInteraction(int buttonNumber){
			// My combination of interaction methods:
			// First button moves in the direction of the wand
			displacement = new alive::interaction::WandDirectionDisplacement(0);
			// Second button pulls the selected object
			pull = new alive::interaction::PullManipulation(1);
			// Third button reorientates the navigation
			rotation = new alive::interaction::WandDirectionDeltaRotation(2);
			// The ray is always casted, we don't need to press any buttons
			raycast = new alive::interaction::WandDirectionRay();
		}

		MyInteraction::~MyInteraction(){
			delete displacement;
			delete pull;
			delete raycast;
			delete rotation;
		}

		void MyInteraction::init(alive::Input* input){
			// The individual methods don't need to overide this method
			// When initing call the parent method (or just store the input in mInput
			alive::InteractionMethod::init(input);
			// And the sub methods also need input of course
			displacement->init(input);
			pull->init(input);
			rotation->init(input);
			raycast->init(input);
		}
		void MyInteraction::update(){
			// have everything update
			displacement->update();
			pull->update();
			rotation->update();
			raycast->update();
		}
	}
}
