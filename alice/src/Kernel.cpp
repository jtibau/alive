#include "Kernel.h"

namespace alice {

	Kernel::Kernel(alice::App* userApp){
		mUserApp = userApp;
	}

	Kernel::~Kernel(){}
}
