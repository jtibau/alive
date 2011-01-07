#include <cstdlib>

#include <vrj/Kernel/Kernel.h>

#include <alice/Kernel.h>
#include <alice/App.h>
#include <alice/InteractionMethod.h>

#include "App.h"

namespace alice {
	namespace juggler {

		/** @addtogroup juggler
		  * @{
		  */
	
		/** @class alice::juggler::Kernel alice/juggler/Kernel.h
		  * @brief Encapsulates what goes on the main function for a VR Juggler App
		  */
		class Kernel : public alice::Kernel {

		public: 

			/** @brief Takes the user's App and instantiates an alice::juggler::App with it. */
			Kernel(alice::App* userApp = 0);

			/** @brief Deletes the juggler app.
			  *
			  * The user's app is deleted by the juggler app.
			  */
			~Kernel();

			/** @brief Inits the kernel and waits for the loop to stop
			  *
			  * Also processes the command line arguments:
			  * Sends the modelname to the user's app
			  * Gives the jconf files to the kernel to configure itself
			  */
			void start(int argc, char* argv[]);
			
			/** @brief Stops the Application */
			void stop();

		private:

			vrj::Kernel* kernel;		/**< The VR Juggler kernel */
			alice::juggler::App* app;	/**< The alice::juggler::App wrapper object */
		};
		/** @} */
	}
}
