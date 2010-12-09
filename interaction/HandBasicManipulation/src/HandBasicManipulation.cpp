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

#include "HandBasicManipulation.h"

#include <alice/InputHandler.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

namespace alice{
    namespace interaction{
        HandBasicManipulation::HandBasicManipulation(int buttonNumber) :
                alice::InteractionMethod(buttonNumber)
        {}

        HandBasicManipulation::~HandBasicManipulation(){}

        void HandBasicManipulation::init(alice::InputHandler *input){
            alice::InteractionMethod::init(input);
            mInput->applySelectionTest(true);
        }

        void HandBasicManipulation::update(){
            if(mInput->objectSelected()){
                if(mInput->getButtonChanged(mButtonNumber)){
                    mInput->applyManipulation( mInput->getButtonState(mButtonNumber) );
                    mInput->applySelectionTest( !mInput->getButtonState(mButtonNumber) );
                }

                if(mInput->getButtonState(mButtonNumber)){
                    gmtl::Vec3f displacement = mInput->getWandPosition(alice::PREVIOUS) - mInput->getWandPosition();
                    gmtl::EulerAngleXYZf rot = gmtl::makeRot<gmtl::EulerAngleXYZf>(mInput->navigationMatrix());
                    gmtl::Matrix44f navigationRotation = gmtl::makeRot<gmtl::Matrix44f>(rot);

                    gmtl::Matrix44f translation = navigationRotation * gmtl::makeTrans<gmtl::Matrix44f>(displacement) * gmtl::makeInvert(navigationRotation);

                    gmtl::Matrix44f transf = translation * mInput->selectedObjectTransformation();

                    mInput->selectedObjectTransformation(transf);
                }
            }
        }
    }
}

