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
