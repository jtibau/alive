#include <alice/juggler/Kernel.h>	// Currently the only kernel for Alice, we use VR Juggler

#include <main/qapplication3d.h>	// The Qt3D header

#include "App.h"					// Our own App class
#include "SceneRenderer.h"			// Our SceneRenderer
#include "MyInteraction.h"			// The Interaction of our choice
#include "ui/UserInterface.h"		// Our user interfaces

// App usage:
//	appName SceneConfigurationFile VRJugglerConfigurationFile(s)
int main(int argc, char* argv[]){
	// Qt3D must be instantiated first of all
	Qt3D::QApplication3D qt3DApp(argc,argv);

	// The poly App subclass is needed in order to handle qt3d stuff
	alice::poly::App* application = new alice::poly::App(
		new alice::poly::SceneRenderer(argv[1]),	// We give our own SceneRendererObject
		new alice::poly::MyInteraction()			// Our prefferred interaction method for this application
	);

	// Instantiate alice's kernel. In this case a VR Juggler kernel
	alice::Kernel* kernel = new alice::juggler::Kernel(application);
	// Start the kernel, give it all the cl args to parse
	kernel->start(argc,argv);

	// Instantiate and show our qt windows
	UserInterface* ui = new UserInterface(NULL);
	ui->setApp(application);
	ui->show();

	// Start the qt thread
	qt3DApp.exec();
	
	// When the qt thread exits it will return control to this thread
	kernel->stop();

	// Delete the kernel and return an success message to the cl
	delete kernel;
	return EXIT_SUCCESS;
}
