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
#include <alive/Scene.h>
#include <alive/InteractionMethod.h>

#include <alive/juggler/App.h>

namespace alive {
	namespace juggler {

		/** @class alive::juggler::Kernel alive/juggler/Kernel.h
		  * @brief Encapsulates what goes on the main function for a VR Juggler App
		  */
		class Kernel {

		public:

			/** @brief Takes the user's App and instantiates an alive::juggler::App with it.
			  */
			Kernel(alive::App* userApp) {
				mUserApp = userApp;
				kernel = vrj::Kernel::instance();	// Get the kernel
				app = new alive::juggler::App(kernel, mUserApp); // Instantiate the app
			}

			/** @brief Deletes the juggler app.
			  *
			  * The user's app is deleted by the juggler app.
			  */
			~Kernel() {
				delete kernel;
				delete app;	// its destructor deletes mUserApp
			}

			/** @brief Inits the kernel and waits for the loop to stop
			  *
			  * Also processes the command line arguments:
			  * Sends the modelname to the user's app
			  * Gives the jconf files to the kernel to configure itself
			  */
			void startAndWait(int argc, char* argv[]) {
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
		private:
			vrj::Kernel* kernel; /**< The VR Juggler kernel */
			alive::juggler::App* app; /**< The alive::juggler::App wrapper object */
			alive::App* mUserApp; /**< The user's App object */
		};
	}
}
