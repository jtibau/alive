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

#define MAX_BUTTONS 3

namespace alive {
	class Scene;
	
	/** @addtogroup alive
	  * @{
	  */
	
	enum Time {
		CURRENT, PREVIOUS
	};

	/** @class alive::Input alive/Input.h
	  * @brief Abstract the user from dealing with devices
	  *
	  * Together with alive::App, this class is integral in creating the abstraction layer
	  * for the user. It provides the user with data from devices, displays and the
	  * running environment.
	  *
	  * Subclasses should implement framework specific initialization and update code.
	  * As well as return correct values for the virtual functions.
	  */
	class Input {

	public:

		/** @brief Default Constructor
		  *
		  * Constructors do very few things in ALIVE, since most initialization happens
		  * in the init method.
		  *
		  * @note The user would most likely not use it, since the App for each framework wrapper
		  *	i.e. alive::juggler::App does the instantiation and passes the object to the user's App.
		  */
		Input();

		/** @brief Default Destructor
		  *
		  * @note As with the default constructor, the App object handles destruction of Input for you.
		  */
		virtual ~Input();

		/** @brief Framework initialization code
		  */
		virtual void init() = 0;

		/** @brief Updates devices and timestamps.
		  */
		virtual void update() = 0;

		/** @brief Returns the context id dinamically, so it is correct wherever it is called.
		  */
		virtual unsigned int getCurrentContext() = 0;

		/** @brief Returns the present time
		  */
		virtual double getCurrentTimeStamp();

		/** @brief Returns the time that has passed since the previous frame
		  */
		virtual float getTimeDelta();

		/** @brief Returns the state of a button
		  *
		  * If the button is pressed, the return value will be true.
		  * The number of buttons is limited by a MAX_BUTTONS global.
		  * If asked for a button number out of range, or an unpressed button, it will return false.
		  */
		virtual bool getButtonState(unsigned int buttonNumber);

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
		
		/** @brief Return flag signaling if a ray has been casted
		  */
		virtual bool getRayCasted();
		/** @brief Set by the interation method that casts the ray
		  */
		virtual void setRayCasted(bool rayCasted);

		/** @brief Returns a 4x4 navigation matrix
		  *
		  * It makes possible to share the navigation matrix between any object.
		  */
		virtual gmtl::Matrix44f getNavigationMatrix();

		/** @brief Stores a new navigation matrix
		  */
		virtual void setNavigationMatrix(gmtl::Matrix44f navigationMatrix);

		/** @brief Returns the transformation to be applied to the selected object
		  */
		virtual gmtl::Matrix44f getSelectedTransformation();
		/** @brief Sets the transformation to be applied to the selected object
		  */ 
		virtual void setSelectedTransformation( gmtl::Matrix44f selectedTransformation );
		/** @brief Returns the current transformation matrix for the selected object
		  * @note Which is how the scene retrieves the manipulation and apply it to
		  * the selected object
		  */
		virtual gmtl::Matrix44f getSelectedObjectMatrix();
		/** @brief Sets a new transformation matrix for the selected object
		  * @note Used by the manipulation method to store the manipulation
		  */
		virtual void setSelectedObjectMatrix( gmtl::Matrix44f selectedObjectMatrix );

		/** @brief Confirms that there is an intersection with a scene object
		  */
		virtual bool getObjectSelectedFlag();
		/** @brief Used by the scene to confirm that there has been an intersection
		  */
		virtual void setObjectSelectedFlag(bool objectSelectedFlag);

		/** @brief Should we apply the manipulation transformation to the selected object
		  */
		virtual bool getApplyManipulation();
		/** @brief The manipulation method sets it to confirm that a manipulation should
		  * take place
		  */
		virtual void setApplyManipulation(bool applyManipulation);
		
		/** @brief Tells the scene if it should be trying out intersections
		  */
		virtual bool getIntersectionCheck();
		/** @brief Sets the intersection check flag
		  */
		virtual void setIntersectionCheck(bool intersectionCheck);

		virtual void lockMutex() = 0;
		virtual void releaseMutex() = 0;

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

	protected:

		gmtl::Vec3f mHeadPosition; /**< Head position */
		gmtl::Vec3f mHeadDirection; /**< Head direction */
		gmtl::Vec3f mPreviousHeadPosition; /**< Previous head position */
		gmtl::Vec3f mPreviousHeadDirection; /**< Previous head direction */
		gmtl::Vec3f mWandPosition; /**< Wand position */
		gmtl::Vec3f mWandDirection; /**< Wand direction */
		gmtl::Vec3f mPreviousWandPosition; /**< Previous Wand Position */
		gmtl::Vec3f mPreviousWandDirection; /**< Previuos Wand Direction */

		gmtl::Vec3f mRayStart; /**< Starting point of the casted ray, it is set by a manipulation method */
		gmtl::Vec3f mRayEnd; /**< End point for the casted ray, set by a manipulation method */
		bool mRayCasted; /**< The manipulation method must set this flag in order to signal that we should try intersecting the ray with the scene */

		bool mButtonState[MAX_BUTTONS]; /**< State of the buttons */

		double mCurrentTime; /**< Current timestamp */
		double mPreviousTime; /**< Previous timestamp */
		float mTimeDelta; /**< Time passed between now and the previous frame */

		gmtl::Matrix44f mNavigationMatrix; /**< The user's navigation matrix */
		gmtl::Matrix44f mSelectedObjectMatrix; /**< Transformation matrix of the interesected/selected object, does not contain the navigation matrix */
		gmtl::Matrix44f mSelectedTransformation; /**< The transformation that will be applied to the selected object */

		bool mObjectSelectedFlag; /**< The scene must set this flag in order to tell the manipulation method that an object has been intersected */
		bool mApplyManipulation; /**< The manipulation method tells the scene that a transformation should be applied to the selected object */
		bool mIntersectionCheck; /**< Flag that indicates if we should be looking for intersections */
	};
	
	/** @} */
}
