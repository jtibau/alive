#include "MyInteraction.h"

namespace alive {
	namespace poly {
		MyInteraction::MyInteraction(int buttonNumber){
			displacement = new alive::interaction::WandDirectionDisplacement(0);
			rotation = new alive::interaction::WandDirectionDeltaRotation(2);
			raycast = new alive::interaction::WandDirectionRay();
		}

		MyInteraction::~MyInteraction(){
			delete displacement;
			delete raycast;
			delete rotation;
		}

		void MyInteraction::init(alive::Input* input){
			alive::InteractionMethod::init(input);
			displacement->init(input);
			rotation->init(input);
			raycast->init(input);
		}
		void MyInteraction::update(){
			displacement->update();
			rotation->update();
			raycast->update();
		}
	}
}
