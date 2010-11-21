#include "InputHandler.h"

namespace alice {
	InputHandler::InputHandler() {}

	InputHandler::~InputHandler() {};

	double InputHandler::getCurrentTimeStamp(){
		return mCurrentTime;
	}

	float InputHandler::getTimeDelta(){
		return mTimeDelta;
	}

	bool InputHandler::getButtonState(unsigned int buttonNumber) {
		if(buttonNumber < MAX_BUTTONS)
			return mButtonState[buttonNumber];
		else return false;
	}
	
	bool InputHandler::getButtonChanged(unsigned int buttonNumber) {
	  if(buttonNumber < MAX_BUTTONS)
			return mButtonChanged[buttonNumber];
		else return false;
	}

	gmtl::Vec3f InputHandler::getHeadPosition(Time t) {
		if(t == PREVIOUS) return mPreviousHeadPosition;
		return mHeadPosition;
	}

	gmtl::Vec3f InputHandler::getHeadDirection(Time t) {
		if(t == PREVIOUS) return mPreviousHeadDirection;
		return mHeadDirection;
	}

	gmtl::Vec3f InputHandler::getWandPosition(Time t) {
		if(t == PREVIOUS) return mPreviousWandPosition;
		return mWandPosition;
	}

	gmtl::Vec3f InputHandler::getWandDirection(Time t) {
		if(t == PREVIOUS) return mPreviousWandDirection;
		return mWandDirection;
	}

	gmtl::Vec3f InputHandler::getRayStart(){ return mRayStart; }
	void InputHandler::setRayStart(gmtl::Vec3f rayStart){ mRayStart = rayStart; }
	gmtl::Vec3f InputHandler::getRayEnd(){ return mRayEnd; }
	void InputHandler::setRayEnd(gmtl::Vec3f rayEnd){ mRayEnd = rayEnd; }
	
	bool InputHandler::getRayCasted() { return mRayCasted; }
	void InputHandler::setRayCasted(bool rayCasted) { mRayCasted = rayCasted; }

	gmtl::Matrix44f InputHandler::getNavigationMatrix(){
		return mNavigationMatrix;
	}

	void InputHandler::setNavigationMatrix(gmtl::Matrix44f navigationMatrix){
		mNavigationMatrix = navigationMatrix;
	}

	gmtl::Matrix44f InputHandler::getSelectedTransformation(){ return mSelectedTransformation; }
	void InputHandler::setSelectedTransformation( gmtl::Matrix44f selectedTransformation ){ mSelectedTransformation = selectedTransformation; }

	gmtl::Matrix44f InputHandler::getSelectedObjectMatrix(){ return mSelectedObjectMatrix; }
	void InputHandler::setSelectedObjectMatrix( gmtl::Matrix44f selectedObjectMatrix ){ mSelectedObjectMatrix = selectedObjectMatrix; }

	bool InputHandler::getObjectSelectedFlag(){ return mObjectSelectedFlag; }
	void InputHandler::setObjectSelectedFlag(bool objectSelectedFlag){ mObjectSelectedFlag = objectSelectedFlag; }

	bool InputHandler::getApplyManipulation(){ return mApplyManipulation; }
	void InputHandler::setApplyManipulation(bool applyManipulation){ mApplyManipulation = applyManipulation; }
	
	bool InputHandler::getIntersectionCheck() { return mIntersectionCheck; }
	void InputHandler::setIntersectionCheck(bool intersectionCheck) { mIntersectionCheck = intersectionCheck; }

}
