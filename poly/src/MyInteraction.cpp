#include "MyInteraction.h"

namespace alive {
	namespace poly {
		MyInteraction::MyInteraction(int buttonNumber){
			displacement = new alive::interaction::WandDirectionDisplacement(0);
			pull = new alive::interaction::PullManipulation(1);
			rotation = new alive::interaction::WandDirectionDeltaRotation(2);
			raycast = new alive::interaction::WandDirectionRay();
		}

		MyInteraction::~MyInteraction(){
			delete displacement;
			delete pull;
			delete raycast;
			delete rotation;
		}

		void MyInteraction::init(alive::Input* input){
			alive::InteractionMethod::init(input);
			displacement->init(input);
			pull->init(input);
			rotation->init(input);
			raycast->init(input);
		}
		void MyInteraction::update(){
			displacement->update();
			pull->update();
			rotation->update();
			raycast->update();
		}
	}
}
