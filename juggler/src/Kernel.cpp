#include "Kernel.h"

namespace alive {
	namespace juggler {

		Kernel::Kernel(alive::App* userApp) :
			alive::Kernel(userApp)
		{
			kernel = vrj::Kernel::instance();	// Get the kernel
			app = new alive::juggler::App(kernel, mUserApp); // Instantiate the app
		}

		/** @brief Deletes the juggler app.
		  *
		  * The user's app is deleted by the juggler app.
		  */
		Kernel::~Kernel() {
			delete app;	// its destructor deletes mUserApp
		}

		/** @brief Inits the kernel and waits for the loop to stop
		  *
		  * Also processes the command line arguments:
		  * Sends the modelname to the user's app
		  * Gives the jconf files to the kernel to configure itself
		  */
		void Kernel::startAndWait(int argc, char* argv[]) {
			if ( argc <= 2 ){
				std::cout << "Usage: " << argv[0]
					<< " modelname vjconfigfile[0] vjconfigfile[1] ... vjconfigfile[n]\n"
					<< std::endl << std::endl;
				std::exit(EXIT_FAILURE);
			}

			mUserApp->setModelName(argv[1]);

			kernel->init(argc, argv);

			// Load any config files specified on the command line
			for ( int i = 2; i < argc; ++i )
				kernel->loadConfigFile(argv[i]);

			kernel->start();

			kernel->setApplication(app);
			kernel->waitForKernelStop();
		}
	}
}
