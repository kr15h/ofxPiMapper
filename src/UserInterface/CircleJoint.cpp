#include "CircleJoint.h"

namespace ofx {
namespace piMapper {

CircleJoint::CircleJoint(){
	setDefaultProperties();
}

void CircleJoint::update(){
	if(!enabled){
		return;
	}
}

void CircleJoint::draw(){
	if(!visible){
		return;
	}
	
	if(!enabled){
		return;
	}
	
	ofEnableAlphaBlending();

	ofPushStyle();
	ofFill();

	if(selected){
		ofSetColor(fillColorSelected);
	}else{
		ofSetColor(fillColor);
	}

	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawCircle(position.x, position.y, radius);
	#else
		ofCircle(position.x, position.y, radius);
	#endif
	ofNoFill();

	if(selected){
		ofSetColor(strokeColorSelected);
	}else{
		ofSetColor(strokeColor);
	}

	ofSetLineWidth(strokeWidth);
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawCircle(position.x, position.y, radius);
	#else
		ofCircle(position.x, position.y, radius);
	#endif
	ofPopStyle();
}

void CircleJoint::setDefaultProperties(){
	radius = 10.0f;
}

bool CircleJoint::hitTest(ofVec2f pos){
	float distance = position.distance(pos);
	if(distance < radius){
		return true;
	}else{
		return false;
	}
}

} // namespace piMapper
} // namespace ofx