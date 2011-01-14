#pragma once

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

#include <alice/InteractionMethod.h>

namespace alice {
  namespace interaction {
    /** @addtogroup interaction
      * @{
      */

    /** @class alice::interaction::GrabRotation alice/interaction/Manipulation/GrabRotation.h
      * @brief Moves the selected object according to the wand's rotation
      */
    class GrabRotation : public alice::InteractionMethod {

    public:

      /** @brief Constructor, calls parent and stores the button number */
      GrabRotation(int buttonNumber = 0) :
          alice::InteractionMethod(buttonNumber)
      {}

      /** @brief Destructor */
      ~GrabRotation(){}

      /** @brief Manipulation methods activate the request for a selection test */
      void init(alice::InputHandler *input){
        alice::InteractionMethod::init(input);
        mInput->applySelectionTest(true);
      }

      /** @brief Rotates the selected object according to the wand's movement */
      void update(){
        // If no object is currently selected, there is no reason to perform a manipulation
        if(mInput->objectSelected()){
          // We must change the interaction flow in two ways when the button changes state
          if(mInput->getButtonChanged(mButtonNumber)){
            // Start or stop manipulating
            mInput->applyManipulation( mInput->getButtonState(mButtonNumber) );
            // Start or stop the selection test
            mInput->applySelectionTest( !mInput->getButtonState(mButtonNumber) );
          }

          // When the button is pressed
          if(mInput->getButtonState(mButtonNumber)){
			gmtl::EulerAngleXYZf prevWandRot = gmtl::makeRot<gmtl::EulerAngleXYZf>(mInput->getWandMatrix(alice::PREVIOUS));
			gmtl::EulerAngleXYZf currWandRot = gmtl::makeRot<gmtl::EulerAngleXYZf>(mInput->getWandMatrix());

			//gmtl::EulerAngleXYZf currRot = currWandRot - prevWandRot;
			gmtl::EulerAngleXYZf currRot;
			currRot[0] = currWandRot[0] - prevWandRot[0];
			currRot[1] = currWandRot[1] - prevWandRot[1];
			currRot[2] = currWandRot[2] - prevWandRot[2];

            gmtl::EulerAngleXYZf navRot = gmtl::makeRot<gmtl::EulerAngleXYZf>(mInput->navigationMatrix());
            gmtl::Matrix44f navigationRotation = gmtl::makeRot<gmtl::Matrix44f>(navRot);

            // Apply the rotation to our translation. We must right multiply the inverse rotation
            // in order to account for said rotation to be applied twice (also in the navigation matrix graph node)
            gmtl::Matrix44f rotation = navigationRotation * gmtl::makeRot<gmtl::Matrix44f>(currRot) * gmtl::makeInvert(navigationRotation);

            gmtl::Matrix44f transf = mInput->selectedObjectTransformation() * rotation;
            mInput->selectedObjectTransformation(transf);
          }
        }
      }
    };
    /** @} */
  }
}
