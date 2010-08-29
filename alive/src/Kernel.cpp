#include "Kernel.h"

namespace alive {

	Kernel::Kernel(alive::App* userApp){
		mUserApp = userApp;
	}

	Kernel::~Kernel(){}
}
