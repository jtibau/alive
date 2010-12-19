#pragma once

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

#include <alice/InteractionMethod.h>

namespace alice {
  namespace interaction {
    /** @addtogroup interaction
      * @{
      */

    /** @class alice::interaction::GrabRotation alice/interaction/Manipulation/GrabRotation.h
      * @brief Moves the selected object according to the wand's displacement
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

      /** @brief Moves the selected object according to the wand's movement */
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
            // We fetch the movement from the wand
            gmtl::Vec3f displacement = mInput->getWandPosition(alice::PREVIOUS) - mInput->getWandPosition();
            // Since the wand's coordinates are relative to the tracker, we must rotate the translation to fit our navigation matrix.
            // We extract the rotation of the navigation matrix
            gmtl::EulerAngleXYZf rot = gmtl::makeRot<gmtl::EulerAngleXYZf>(mInput->navigationMatrix());
            gmtl::Matrix44f navigationRotation = gmtl::makeRot<gmtl::Matrix44f>(rot);

            // Apply the rotation to our translation. We must right multiply the inverse rotation
            // in order to account for said rotation to be applied twice (also in the navigation matrix graph node)
            gmtl::Matrix44f translation = navigationRotation * gmtl::makeTrans<gmtl::Matrix44f>(displacement) * gmtl::makeInvert(navigationRotation);

            // add a translation to the objects transformation matrix
            gmtl::Matrix44f transf = translation * mInput->selectedObjectTransformation();
            // store the matrix so the scene can fetch it
            mInput->selectedObjectTransformation(transf);
          }
        }
      }
    };
    /** @} */
  }
}
