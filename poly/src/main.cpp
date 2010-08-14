/******************************************************************************
 *
 *	This library is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include <cstdlib>

#include <vrj/Kernel/Kernel.h>

#include <alive/App.h>
#include <alive/juggler/App.h>

#include <alive/interaction/BasicNavigation.h>

#include "Scene.h"

int main(int argc, char* argv[]){
	if ( argc <= 2 ){
		std::cout << "Usage: " << argv[0]
			<< " modelname vjconfigfile[0] vjconfigfile[1] ... vjconfigfile[n]\n"
			<< std::endl << std::endl;

		std::exit(EXIT_FAILURE);
	}

	vrj::Kernel* kernel = vrj::Kernel::instance();	// Get the kernel
	alive::App* application = new alive::App( new alive::poly::Scene() , new alive::interaction::BasicNavigation() );
	alive::juggler::App* app = new alive::juggler::App(kernel, application); // Instantiate the app

	application->setModelName(argv[1]);

	kernel->init(argc, argv);

	// Load any config files specified on the command line
	for ( int i = 2; i < argc; ++i )
		kernel->loadConfigFile(argv[i]);

	kernel->start();

	kernel->setApplication(app);
	kernel->waitForKernelStop();

	delete application;

	return EXIT_SUCCESS;
}
