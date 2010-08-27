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

#include "Scene.h"
#include "MyInteraction.h"

int main(int argc, char* argv[]){
	alive::App* application = new alive::App( new alive::poly::Scene() ,
		new alive::poly::MyInteraction() );
	
	alive::Kernel* kernel = new alive::juggler::Kernel(application);

	kernel->startAndWait(argc,argv);
	delete kernel;
	return EXIT_SUCCESS;
}
