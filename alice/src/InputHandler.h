#pragma once

#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>

#include <string>

#define MAX_BUTTONS 13

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

		/** @brief Framework initialization code */
		virtual void init() = 0;

		/** @brief Updates devices and timestamps. */
		virtual void update() = 0;

		/////////////////////// SYSTEM ///////////////////////

		/** @brief Returns the context id dinamically, so it is correct wherever it is called. */
		virtual unsigned int getCurrentContext() = 0;

		/** @brief Returns the present time */
		virtual double getCurrentTimeStamp();

		/** @brief Returns the time that has passed since the previous frame */
		virtual float getTimeDelta();

		/** @brief Returns the viewport for the context where it is called
		  *
		  * @note The returned array is laid out as {originX, originY, width, height}
		  */
		virtual const int* getViewport() = 0;

		/** @brief Returns the 4x4 view matrix for the current projection */
		virtual const float* getViewMatrix() = 0;

		/** @brief Returns the frustum values for the current context
		  *
		  * The returned array is laid out as {left, right, bottom, top, near, far}
		  */
		virtual const float* getFrustum() = 0;

		/** @brief Locks the mutex, needed if running a cluster or multi-system configuration */
		virtual void lockMutex() = 0;
		
		/** @brief Unlocks the mutex, needed if running a cluster or multi-system configuration */
		virtual void releaseMutex() = 0;

		/////////////////////// INPUT ///////////////////////

		/** @brief Returns the state of a button
		  *
		  * If the button is pressed, the return value will be true.
		  * The number of buttons is limited by a MAX_BUTTONS global.
		  * If asked for a button number out of range, or an unpressed button, it will return false.
		  */
		virtual bool getButtonState(unsigned int buttonNumber);

		/** @brief Returns true if the button just changed state. */
		virtual bool getButtonChanged(unsigned int buttonNumber);

		/** @brief Returns a 3D vector with the head position
		  *
		  * The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
		virtual gmtl::Vec3f getHeadPosition(Time t = CURRENT);

		/** @brief Returns a 3D vector with the head direction
		  *
		  * The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
		virtual gmtl::Vec3f getHeadDirection(Time t = CURRENT);

		/** @brief Returns a 3D vector with the wand position
		  *
		  * The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
		virtual gmtl::Vec3f getWandPosition(Time t = CURRENT);

		/** @brief Returns a 3D vector with the wand direction
		  *
		  * The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
		virtual gmtl::Vec3f getWandDirection(Time t = CURRENT);

		/** @brief Returns a 4x4 matrix with the head data
		  *
		  * The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
		virtual gmtl::Matrix44f getHeadMatrix(Time t = CURRENT);

		/** @brief Returns a 4x4 matrix with the wand data
		  *
		  * The two possible time values are CURRENT and PREVIOUS. These are stored
		  * and provided in case some interaction methods need them.
		  */
		virtual gmtl::Matrix44f getWandMatrix(Time t = CURRENT);

		/** @brief Returns the starting point of the casted ray */
		virtual gmtl::Vec3f getRayStart();
		
		/** @brief Stores the starting point of the casted ray */
		virtual void setRayStart(gmtl::Vec3f rayStart);
		
		/** @brief Returns the end point of the casted ray */
		virtual gmtl::Vec3f getRayEnd();
		
		/** @brief Stores the end point of the casted ray */
		virtual void setRayEnd(gmtl::Vec3f rayEnd);

		/////////////////////// INTERACTION ///////////////////////

		/** @brief Stores the url of the configuration file */
		virtual void sceneConfigurationFile(std::string scene) { mSceneConfigurationFile = scene; }
		/** @brief Gets the scene configuration filename set upon instantiation */
		virtual std::string sceneConfigurationFile() { return mSceneConfigurationFile; }

		/** @brief Toggles the selection test flag */
		virtual void applySelectionTest(bool flag){ mSelectionTestFlag = flag; }
		/** @brief Gets the state of the selection test */
		virtual bool applySelectionTest(){ return mSelectionTestFlag; }

		/** @brief Toggles the flag that indicates if an object is selected */
		virtual void objectSelected(bool flag){ mObjectSelectedFlag = flag; }
		/** @brief Indicates if there is an object selected */
		virtual bool objectSelected(){ return mObjectSelectedFlag; }

		/** @brief Toggles the flag to mandate object manipulation */
		virtual void applyManipulation(bool flag){ mManipulationFlag = flag; }
		/** @brief Indicates if we should apply the manipulation matrices to the selected object */
		virtual bool applyManipulation(){ return mManipulationFlag; }

		/** @brief Toggles the scaling flag */
		virtual void applyScaling(bool flag){ mScalingFlag = flag; }
		/** @brief Indicates if we should replace the scaling matrix of the selected object */
		virtual bool applyScaling(){ return mScalingFlag; }
		
		/** @brief Toggles the flag that indicates if we should update the navigation matrix */
		virtual void applyNavigation(bool flag){ mNavigationFlag = flag; }
		/** @brief Indicates if we should update the navigation matrix */
		virtual bool applyNavigation(){ return mNavigationFlag; }

		/** @brief Replaces the navigation matrix */
		virtual void navigationMatrix(gmtl::Matrix44f  matrix){ mNavigationMatrix = matrix; }
		/** @brief Gets the current navigation matrix */
		virtual gmtl::Matrix44f navigationMatrix(){ return mNavigationMatrix; }

		/** @brief Substitutes the selected object's translation and rotation matrix */
		virtual void selectedObjectTransformation(gmtl::Matrix44f  matrix){ mSelectedTransformation = matrix; }
		/** @brief Gets the current selected object's translation and rotation matrix */
		virtual gmtl::Matrix44f selectedObjectTransformation(){ return mSelectedTransformation; }

		/** @brief Substitutes the selected object's scaling matrix */
		virtual void selectedObjectScalingMatrix(gmtl::Matrix44f matrix){ mSelectedScale = matrix; }
		/** @brief Gets the current selected object's scaling matrix */
		virtual gmtl::Matrix44f selectedObjectScalingMatrix(){ return mSelectedScale; }

		/** @brief Signal the Scene to center the models */
		virtual void centerModels(bool flag){ mCenterFlag = flag; }
		/** @brief Query if we should center the models */
		virtual bool centerModels(){ return mCenterFlag; }

	protected:

		gmtl::Vec3f			mHeadPosition;					/**< Head position */
		gmtl::Vec3f			mHeadDirection;					/**< Head direction */
		gmtl::Vec3f			mPreviousHeadPosition;			/**< Previous head position */
		gmtl::Vec3f			mPreviousHeadDirection;			/**< Previous head direction */
		gmtl::Vec3f			mWandPosition;					/**< Wand position */
		gmtl::Vec3f			mWandDirection;					/**< Wand direction */
		gmtl::Vec3f			mPreviousWandPosition;			/**< Previous Wand Position */
		gmtl::Vec3f			mPreviousWandDirection;			/**< Previuos Wand Direction */

		gmtl::Matrix44f 	mWandMatrix;					/**< Unprocessed wand matrix */
		gmtl::Matrix44f 	mHeadMatrix;					/**< Unprocessed head matrix */
		
		gmtl::Matrix44f 	mPreviousWandMatrix;			/**< Previous wand matrix */
		gmtl::Matrix44f 	mPreviousHeadMatrix;			/**< Previous head matrix */

		bool				mButtonState[MAX_BUTTONS];		/**< State of the buttons */
		bool				mButtonChanged[MAX_BUTTONS];	/**< Buttons' state change flag */

		double				mCurrentTime;					/**< Current timestamp */
		double				mPreviousTime;					/**< Previous timestamp */
		float				mTimeDelta;						/**< Time passed between now and the previous frame */

		/** String holding the configuration file for the scene.
		  * A csv file with model filenames and transformations
		  */
		std::string			mSceneConfigurationFile;

		bool				mSelectionTestFlag;				/**< Flag that indicates if we should be looking for intersections */
		bool				mObjectSelectedFlag;			/**< The scene must set this flag in order to tell the manipulation method that an object has been intersected */
		bool				mManipulationFlag;				/**< The manipulation method tells the scene that a transformation should be applied to the selected object */
		bool				mScalingFlag;					/**< A scaling manipulation method alerts the scene that a scaling has to be applied to the selected object */
		bool				mNavigationFlag;				/**< Apply Navigation */
		bool				mCenterFlag;					/**< Indicates scene to center models */

		gmtl::Vec3f			mRayStart;						/**< Starting point of the casted ray, it is set by a manipulation method */
		gmtl::Vec3f			mRayEnd;						/**< End point for the casted ray, set by a manipulation method */

		gmtl::Matrix44f		mNavigationMatrix;				/**< The user's navigation matrix */
		gmtl::Matrix44f		mSelectedTransformation;		/**< The transformation that will be applied to the selected object */
		gmtl::Matrix44f		mSelectedScale;					/**< The scaling that will be applied to the selected object */
	};

	/** @} */
}
