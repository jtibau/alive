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

#pragma once

namespace alice {
	class App;
	
	/** @addtogroup alice
	  * @{
	  */
	

	/** @class alice::Kernel alice/Kernel.h
	  * @brief Simplifies the startup process, so the main can be more abstracted from
	  *	framework specific calls
	  */
	class Kernel {
	public:
		/** @brief Instantiates any possible objects and sotres a pointer to the 
		  * 	user's App
		  */
		Kernel(alice::App* userApp = 0);

		/** @brief Deletes any objects instantiated on constructor
		  */
		virtual ~Kernel();
	
		/** @brief Processes command line arguments, starts the control loop
		  *	and holds until App termination
		  */
		virtual void start(int argc, char* argv[]) = 0;
		
		virtual void stop() = 0;
		
	protected:
		/** @brief The user's App
		  * 
		  * Could be a sub-class, but might as well be the alice::App fed with
		  * your own Scene and InteractionMethods
		  */
		alice::App* mUserApp;
	};
	/** @} */
}
