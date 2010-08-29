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

#include <gmtl/Matrix.h>

namespace alive {
	class Input;
	
	/** @addtogroup alive
	  * @{
	  */
	

	/** @class alive::Scene alive/Scene.h
	  * @brief The abstract Scene class
	  *
	  * Subclasses will hold all of the rendering code for the application.
	  * @note Basiccally alive::App calls mScene methods of the same name.
	  */
	class Scene {

	public:

		/**	@brief Default constructor
		  */
		Scene();

		/**	@brief Default destructor
		  */
		virtual ~Scene();

		/** @brief Initialization code
		  *
		  * This call happens before entering a specific OpenGL context.
		  * Don't load any textures, lists or opengl ids here.
		  */
		virtual void init(Input* input);

		/** @brief Initialization code that requires an OpenGL context
		  *
		  * Use the special template vrj::opengl::ContextData
		  * #include <vrj/Draw/OpenGL/ContextData.h>
		  * An object of this type will behave as a pointer to the correct id/object for each context,
		  * since each context might assign different ids for loaded textures or other objects,
		  * this is necessary for abstraction.
		  */
		virtual void contextInit() = 0;

		/** @brief Is called once per frame, just before drawing.
		  *
		  * Scene update code should be placed here. Howerver this is still not inside and OpenGL context
		  */
		virtual void latePreFrame() = 0;

		/** @brief Called once for each draw buffer
		  *
		  * The App clears the color buffer for you. Keep it short since it will increase latency.
		  */
		virtual void bufferPreDraw() = 0;

		/** @brief Called for each viewport, should hold all of the scene's drawing calls.
		  *
		  * The App clears the Depth buffer and pushes the necessary attributes, as well as the
		  * modelview and projection matrix. Afer mScene->Draw() happens, it pops the matrices and attribs
		  * from the stack.
		  */
		virtual void draw() = 0;

		/** @brief Stores the model's file name until an appropriate time to load (contextInit).
		  */
		virtual void setModelName(char* modelFileName);

	protected:

		Input* mInput; /**< Pointer to the Input object */
		char* mFileToLoad; /**< The filename of the model to be loaded */
	};
	
	/** @} */
}
