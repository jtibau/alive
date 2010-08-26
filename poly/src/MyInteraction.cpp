#include <alive/poly/MyInteraction.h>

namespace alive {
	namespace poly {
		void MyInteraction::update(){
			displacement->update();
//			rotation->update();
		}
	}
}
