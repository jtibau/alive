#pragma once

namespace alice {
	class InputHandler;

	/** @addtogroup alice
	  * @{
	  */
	

	/** @class alice::InteractionMethod alice/InteractionMethod.h
	  * @brief Interface to any type of Interaction Method
	  * (navigation, selection, manipulation).
	  *
	  * Most of the subclasses' work should get done in update.
	  * Changes reported to the Scene
	  * through signals and slots, or alice::InputHandler
	  */
	class InteractionMethod {

	public:
		/** @brief Default constructor
		  *
		  * Stores the buttonNumber, optionally just the first button
		  */
		InteractionMethod(unsigned int buttonNumber = 0);

		/** @brief Destructor
		  *
		  * @note Does nothing, but subclasses might
		  */
		virtual ~InteractionMethod();

		/** @brief Initialization code
		  *
		  * @note Most importantly it needs to keep the input pointer
		  */
		virtual void init(InputHandler* input);

		/** @brief Update code specific to the method
		  */
		virtual void update() = 0;

	protected:
		unsigned int mButtonNumber; /**< Button id that activates the method */
		InputHandler* mInput; /**< Pointer to the InputHandler object */
	};
	/** @} */
}
