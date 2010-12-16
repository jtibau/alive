#include "InteractionMethod.h"

namespace alice {
	InteractionMethod::InteractionMethod(unsigned int buttonNumber) :
		mButtonNumber(buttonNumber){}

	InteractionMethod::~InteractionMethod(){}

	void InteractionMethod::init(InputHandler* input){ mInput = input; }
}
