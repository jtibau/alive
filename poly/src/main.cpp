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

#include <alive/App.h>
#include <alive/juggler/Kernel.h>

#include "App.h"
#include "Scene.h"
#include "MyInteraction.h"

#include <main/qapplication3d.h>

#include <iostream>

int main(int argc, char* argv[]){

  Qt3D::QApplication3D qt3DApp(argc,argv);

	// Since this application does fairly standard stuff,
	// we don't need to subclass alive:App
	alive::poly::App* application = new alive::poly::App(
		new alive::poly::Scene(),				// Our Scene
		new alive::poly::MyInteraction()		// Just a mix of available methods
	);
	
	// This is the *only* line that ties the project to vrjuggler
	// Not yet, cause we still have to replace ContexData and the Mutex
	alive::Kernel* kernel = new alive::juggler::Kernel(application);
	kernel->start(argc,argv);
    
  qt3DApp.setQuitOnLastWindowClosed(false);
  qt3DApp.exec();
  
  
  std::cout << "Stopping backend kernel\n";
  kernel->stop();
  std::cout << "Backend kernel stopped\n";
	
	// clean up
	delete kernel;
	return EXIT_SUCCESS;
}
