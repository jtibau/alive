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
	
	gmtl::Matrix44f InputHandler::getHeadMatrix(Time t){
		if(t == PREVIOUS) return mPreviousHeadMatrix;
		return mHeadMatrix;
	}
	
	gmtl::Matrix44f InputHandler::getWandMatrix(Time t){
		if(t == PREVIOUS) return mPreviousWandMatrix;
		return mWandMatrix;
	}

	gmtl::Vec3f InputHandler::getRayStart(){ return mRayStart; }
	void InputHandler::setRayStart(gmtl::Vec3f rayStart){ mRayStart = rayStart; }
	gmtl::Vec3f InputHandler::getRayEnd(){ return mRayEnd; }
	void InputHandler::setRayEnd(gmtl::Vec3f rayEnd){ mRayEnd = rayEnd; }
}
