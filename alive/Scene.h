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

	class Scene {

	public:

		Scene() {}
		virtual ~Scene() {}

		virtual void init(Input* input) {
			mInput = input;
		}

		virtual void contextInit() = 0;

		virtual void latePreFrame() = 0;
		virtual void draw() = 0;

		virtual void setModelName(char* modelFileName) { mFileToLoad = modelFileName; }
		virtual void navigationMatrixChanged(const float* navigationMatrix) = 0;

	protected:
		Input* mInput;
		char* mFileToLoad;
	};
}
