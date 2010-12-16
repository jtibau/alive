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

#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>

#include <string>

#define MAX_BUTTONS 12

namespace alice {
    class Scene;

    /** @addtogroup alice
	  * @{
	  */

    enum Time {
        CURRENT, PREVIOUS
            };

    /** @class alice::InputHandler alice/InputHandler.h
	  * @brief Abstract the user from dealing with devices
	  *
	  * Together with alice::App, this class is integral in creating the abstraction layer
	  * for the user. It provides the user with data from devices, displays and the
	  * running environment.
	  *
	  * Subclasses should implement framework specific initialization and update code.
	  * As well as return correct values for the virtual functions.
	  */
    class InputHandler {

    public:

        /** @brief Default Constructor
		  *
		  * Constructors do very few things in ALICE, since most initialization happens
		  * in the init method.
		  *
		  * @note The user would most likely not use it, since the App for each framework wrapper
		  *	i.e. alice::juggler::App does the instantiation and passes the object to the user's App.
		  */
        InputHandler();

        /** @brief Default Destructor
		  *
		  * @note As with the default constructor, the App object handles destruction of InputHandler for you.
		  */
        virtual ~InputHandler();

        /** @brief Framework initialization code
		  */
        virtual void init() = 0;

        /** @brief Updates devices and timestamps.
		  */
        virtual void update() = 0;

        /////////////////////// SYSTEM ///////////////////////

        /** @brief Returns the context id dinamically, so it is correct wherever it is called.
		  */
        virtual unsigned int getCurrentContext() = 0;

        /** @brief Returns the present time
		  */
        virtual double getCurrentTimeStamp();

        /** @brief Returns the time that has passed since the previous frame
		  */
        virtual float getTimeDelta();

        /** @brief Returns the viewport for the context where it is called
			*
			* The returned array is laid out as {originX, originY, width, height}
			*/
        virtual const int* getViewport() = 0;

        /** @brief Returns the 4x4 view matrix for the current projection
			*/
        virtual const float* getViewMatrix() = 0;

        /** @brief Returns the frustum values for the current context
			*
			* The returned array is laid out as {left, right, bottom, top, near, far}
			*/
        virtual const float* getFrustum() = 0;

        virtual void lockMutex() = 0;
        virtual void releaseMutex() = 0;

        /////////////////////// INPUT ///////////////////////

        /** @brief Returns the state of a button
		  *
		  * If the button is pressed, the return value will be true.
		  * The number of buttons is limited by a MAX_BUTTONS global.
		  * If asked for a button number out of range, or an unpressed button, it will return false.
		  */
        virtual bool getButtonState(unsigned int buttonNumber);

        virtual bool getButtonChanged(unsigned int buttonNumber);

        /** @brief Returns a 3D vector with the head position
		  *
		  *	The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
        virtual gmtl::Vec3f getHeadPosition(Time t = CURRENT);

        /** @brief Returns a 3D vector with the head direction
		  *
		  *	The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
        virtual gmtl::Vec3f getHeadDirection(Time t = CURRENT);

        /** @brief Returns a 3D vector with the wand position
		  *
		  *	The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
        virtual gmtl::Vec3f getWandPosition(Time t = CURRENT);

        /** @brief Returns a 3D vector with the wand direction
		  *
		  *	The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
        virtual gmtl::Vec3f getWandDirection(Time t = CURRENT);

        /** @brief Returns the starting point of the casted ray
		  */
        virtual gmtl::Vec3f getRayStart();
        /** @brief Stores the starting point of the casted ray
		  */
        virtual void setRayStart(gmtl::Vec3f rayStart);
        /** @brief Returns the end point of the casted ray
		  */
        virtual gmtl::Vec3f getRayEnd();
        /** @brief Stores the end point of the casted ray
		  */
        virtual void setRayEnd(gmtl::Vec3f rayEnd);

        /////////////////////// INTERACTION ///////////////////////

        virtual void sceneConfigurationFile(std::string scene) { mSceneConfigurationFile = scene; }
        virtual std::string sceneConfigurationFile() { return mSceneConfigurationFile; }

        virtual void applySelectionTest(bool flag){mSelectionTestFlag = flag;}
        virtual bool applySelectionTest(){return mSelectionTestFlag;}

        virtual void objectSelected(bool flag){mObjectSelectedFlag = flag;}
        virtual bool objectSelected(){return mObjectSelectedFlag;}

        virtual void applyManipulation(bool flag){mManipulationFlag = flag;}
        virtual bool applyManipulation(){return mManipulationFlag;}

        virtual void applyNavigation(bool flag){mNavigationFlag = flag;}
        virtual bool applyNavigation(){return mNavigationFlag;}

        virtual void navigationMatrix(gmtl::Matrix44f  matrix){mNavigationMatrix = matrix;}
        virtual gmtl::Matrix44f navigationMatrix(){return mNavigationMatrix;}

        virtual void selectedObjectTransformation(gmtl::Matrix44f  matrix){mSelectedTransformation = matrix;}
        virtual gmtl::Matrix44f selectedObjectTransformation(){return mSelectedTransformation;}

    protected:

        gmtl::Vec3f       mHeadPosition;								/**< Head position */
        gmtl::Vec3f       mHeadDirection;								/**< Head direction */
        gmtl::Vec3f       mPreviousHeadPosition;				/**< Previous head position */
        gmtl::Vec3f       mPreviousHeadDirection;				/**< Previous head direction */
        gmtl::Vec3f       mWandPosition;								/**< Wand position */
        gmtl::Vec3f       mWandDirection;								/**< Wand direction */
        gmtl::Vec3f       mPreviousWandPosition;				/**< Previous Wand Position */
        gmtl::Vec3f       mPreviousWandDirection;				/**< Previuos Wand Direction */

        bool              mButtonState[MAX_BUTTONS];		/**< State of the buttons */
        bool              mButtonChanged[MAX_BUTTONS];	/**< True if there was a state change in the current frame */

        double            mCurrentTime;									/**< Current timestamp */
        double            mPreviousTime;								/**< Previous timestamp */
        float             mTimeDelta;										/**< Time passed between now and the previous frame */

        std::string       mSceneConfigurationFile;      /**< String holding the configuration file for the scene. A csv file with model filenames and transformations */

        bool							mSelectionTestFlag;						/**< Flag that indicates if we should be looking for intersections */
        bool							mObjectSelectedFlag;					/**< The scene must set this flag in order to tell the manipulation method that an object has been intersected */
        bool							mManipulationFlag;						/**< The manipulation method tells the scene that a transformation should be applied to the selected object */
        bool							mNavigationFlag;							/**< Apply Navigation */

        gmtl::Vec3f       mRayStart;										/**< Starting point of the casted ray, it is set by a manipulation method */
        gmtl::Vec3f       mRayEnd;											/**< End point for the casted ray, set by a manipulation method */

        gmtl::Matrix44f   mNavigationMatrix;						/**< The user's navigation matrix */
        gmtl::Matrix44f   mSelectedObjectMatrix;				/**< Transformation matrix of the interesected/selected object, does not contain the navigation matrix */
        gmtl::Matrix44f   mSelectedTransformation;			/**< The transformation that will be applied to the selected object */
    };

    /** @} */
}
