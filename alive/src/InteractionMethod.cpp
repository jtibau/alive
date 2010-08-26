#include "InteractionMethod.h"

namespace alive {
		InteractionMethod::InteractionMethod(unsigned int buttonNumber) :
			mButtonNumber(buttonNumber){}

	InteractionMethod::~InteractionMethod(){}

	void InteractionMethod::init(Input* input){ mInput = input; }

	void InteractionMethod::draw(){}
}
