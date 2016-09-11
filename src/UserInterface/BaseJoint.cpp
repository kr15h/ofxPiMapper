#include "BaseJoint.h"

namespace ofx {
namespace piMapper {

BaseJoint::BaseJoint(){
	setDefaultColors();
	setDefaultProperties();
	registerMouseEvents();
}

BaseJoint::~BaseJoint(){
	unregisterMouseEvents();
}

void BaseJoint::registerMouseEvents(){
	//ofAddListener(ofEvents().mousePressed, this, &BaseJoint::mousePressed);
	//ofAddListener(ofEvents().mouseDragged, this, &BaseJoint::mouseDragged);
}

void BaseJoint::unregisterMouseEvents(){
	//ofRemoveListener(ofEvents().mousePressed, this, &BaseJoint::mousePressed);
	//ofRemoveListener(ofEvents().mouseDragged, this, &BaseJoint::mouseDragged);
}

void BaseJoint::mousePressed(ofMouseEventArgs & args){
	cout << "BaseJoint::mousePressed()" << endl;

	if(hitTest(ofVec2f(args.x, args.y))){
		// selected = true;
		clickDistance = position - ofVec2f(args.x, args.y);
		// startDrag();
	}
}

void BaseJoint::mouseReleased(int x, int y, int button){
	stopDrag();
}

void BaseJoint::mouseDragged(ofMouseEventArgs & args){
	cout << "BaseJoint::mouseDragged()" << endl;
	
	if(!bDrag){
		return;
	}
	position = ofVec2f(args.x, args.y) + clickDistance;
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

void BaseJoint::setClickDistance(ofVec2f newClickDistance){
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
	position = ofVec2f(20.0f, 20.0f);
	clickDistance = ofVec2f(0.0f, 0.0f);
	bDrag = false;
	selected = false;
	strokeWidth = 1.5f;
}

} // namespace piMapper
} // namespace ofx