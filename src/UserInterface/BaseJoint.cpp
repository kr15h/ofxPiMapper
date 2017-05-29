#include "BaseJoint.h"

namespace ofx {
namespace piMapper {

BaseJoint::BaseJoint(){
	setDefaultColors();
	setDefaultProperties();
}

void BaseJoint::mousePressed(ofMouseEventArgs & args){
	if(hitTest(ofDefaultVec2(args.x, args.y))){
		clickDistance = position - ofDefaultVec2(args.x, args.y);
	}
}

void BaseJoint::mouseReleased(int x, int y, int button){
	stopDrag();
}

void BaseJoint::mouseDragged(ofMouseEventArgs & args){
	if(!bDrag){
		return;
	}
	position = ofDefaultVec2(args.x, args.y) + clickDistance;
}

void BaseJoint::startDrag(){
	bDrag = true;
}

void BaseJoint::stopDrag(){
	bDrag = false;
}

void BaseJoint::select(){
	selected = true;
}

void BaseJoint::unselect(){
	selected = false;
}

void BaseJoint::setClickDistance(ofDefaultVec2 newClickDistance){
	clickDistance = newClickDistance;
}

bool BaseJoint::isDragged(){
	return bDrag;
}

bool BaseJoint::isSelected(){
	return selected;
}

void BaseJoint::setDefaultColors(){
	fillColor = ofColor(0, 255, 255, 0);
	strokeColor = ofColor(255, 255, 255);
	fillColorSelected = ofColor(255, 255, 0, 0);
	strokeColorSelected = ofColor(255, 0, 0);
}

void BaseJoint::setDefaultProperties(){
	enabled = true;
	visible = true;
	position = ofDefaultVec2(20.0f, 20.0f);
	clickDistance = ofDefaultVec2(0.0f, 0.0f);
	bDrag = false;
	selected = false;
	strokeWidth = 1.5f;
}

} // namespace piMapper
} // namespace ofx