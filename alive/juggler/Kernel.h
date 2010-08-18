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
		class Kernel {
		public:
			Kernel(alive::App* userApp) {
				mUserApp = userApp;
				kernel = vrj::Kernel::instance();	// Get the kernel
				app = new alive::juggler::App(kernel, mUserApp); // Instantiate the app
			}

			~Kernel() {
				delete app;
			}

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
		protected:
			vrj::Kernel* kernel;
			alive::juggler::App* app;
			alive::App* mUserApp;
		};
	}
}
