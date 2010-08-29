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

namespace alive {
	class Input;

	/** @class alive::InteractionMethod alive/InteractionMethod.h
	  * @brief Interface to any type of Interaction Method
	  * (navigation, selection, manipulation).
	  *
	  * Most of the subclasses' work should get done in update.
	  * Changes reported to the Scene
	  * through signals and slots, or alive::Input
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
		virtual void init(Input* input);

		/** @brief Update code specific to the method
		  */
		virtual void update() = 0;

		/** @brief Optional place to place opengl code.
		  *
		  * @note Does nothing for the moment
		  */
		virtual void draw();

	protected:
		unsigned int mButtonNumber; /**< Button id that activates the method */
		Input* mInput; /**< Pointer to the Input object */
	};
}
