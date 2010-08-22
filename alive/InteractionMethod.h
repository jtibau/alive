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
	class InteractionMethod {
	public:
		InteractionMethod(){}
		virtual ~InteractionMethod(){}

		virtual void init(Input* input){ mInput = input; }

		virtual void update() = 0;

		virtual void draw(){}
	protected:
		Input* mInput;
	};
}
