#include "Input.h"

namespace alive {
	Input::Input() {}

	Input::~Input() {};

	double Input::getCurrentTimeStamp(){
		return mCurrentTime;
	}

	float Input::getTimeDelta(){
		return mTimeDelta;
	}

	bool Input::getButtonState(unsigned int buttonNumber) {
		if(buttonNumber < MAX_BUTTONS)
			return mButtonState[buttonNumber];
		else return false;
	}
	
	bool Input::getButtonChanged(unsigned int buttonNumber) {
	  if(buttonNumber < MAX_BUTTONS)
			return mButtonChanged[buttonNumber];
		else return false;
	}

	gmtl::Vec3f Input::getHeadPosition(Time t) {
		if(t == PREVIOUS) return mPreviousHeadPosition;
		return mHeadPosition;
	}

	gmtl::Vec3f Input::getHeadDirection(Time t) {
		if(t == PREVIOUS) return mPreviousHeadDirection;
		return mHeadDirection;
	}

	gmtl::Vec3f Input::getWandPosition(Time t) {
		if(t == PREVIOUS) return mPreviousWandPosition;
		return mWandPosition;
	}

	gmtl::Vec3f Input::getWandDirection(Time t) {
		if(t == PREVIOUS) return mPreviousWandDirection;
		return mWandDirection;
	}

	gmtl::Vec3f Input::getRayStart(){ return mRayStart; }
	void Input::setRayStart(gmtl::Vec3f rayStart){ mRayStart = rayStart; }
	gmtl::Vec3f Input::getRayEnd(){ return mRayEnd; }
	void Input::setRayEnd(gmtl::Vec3f rayEnd){ mRayEnd = rayEnd; }
	
	bool Input::getRayCasted() { return mRayCasted; }
	void Input::setRayCasted(bool rayCasted) { mRayCasted = rayCasted; }

	gmtl::Matrix44f Input::getNavigationMatrix(){
		return mNavigationMatrix;
	}

	void Input::setNavigationMatrix(gmtl::Matrix44f navigationMatrix){
		mNavigationMatrix = navigationMatrix;
	}

	gmtl::Matrix44f Input::getSelectedTransformation(){ return mSelectedTransformation; }
	void Input::setSelectedTransformation( gmtl::Matrix44f selectedTransformation ){ mSelectedTransformation = selectedTransformation; }

	gmtl::Matrix44f Input::getSelectedObjectMatrix(){ return mSelectedObjectMatrix; }
	void Input::setSelectedObjectMatrix( gmtl::Matrix44f selectedObjectMatrix ){ mSelectedObjectMatrix = selectedObjectMatrix; }

	bool Input::getObjectSelectedFlag(){ return mObjectSelectedFlag; }
	void Input::setObjectSelectedFlag(bool objectSelectedFlag){ mObjectSelectedFlag = objectSelectedFlag; }

	bool Input::getApplyManipulation(){ return mApplyManipulation; }
	void Input::setApplyManipulation(bool applyManipulation){ mApplyManipulation = applyManipulation; }
	
	bool Input::getIntersectionCheck() { return mIntersectionCheck; }
	void Input::setIntersectionCheck(bool intersectionCheck) { mIntersectionCheck = intersectionCheck; }

}
