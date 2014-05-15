#include "ofxBaseJoint.h"

ofxBaseJoint::ofxBaseJoint()
{
    setDefaultColors();
    setDefaultProperties();
    registerMouseEvents();
}

ofxBaseJoint::~ofxBaseJoint()
{
    unregisterMouseEvents();
}

void ofxBaseJoint::registerMouseEvents()
{
    ofAddListener(ofEvents().mousePressed, this, &ofxBaseJoint::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxBaseJoint::mouseDragged);
}

void ofxBaseJoint::unregisterMouseEvents()
{
    ofRemoveListener(ofEvents().mousePressed, this, &ofxBaseJoint::mousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxBaseJoint::mouseDragged);
}

void ofxBaseJoint::mousePressed(ofMouseEventArgs& args)
{
    if ( hitTest(ofVec2f(args.x, args.y)) ) {
        //selected = true;
        clickDistance = position - ofVec2f(args.x, args.y);
        //startDrag();
    }
}

void ofxBaseJoint::mouseReleased(int x, int y, int button)
{
    stopDrag();
}

void ofxBaseJoint::mouseDragged(ofMouseEventArgs& args)
{
    if ( !bDrag ) return;
    position = ofVec2f(args.x, args.y) + clickDistance;
}

void ofxBaseJoint::startDrag()
{
    bDrag = true;
}

void ofxBaseJoint::stopDrag()
{
    bDrag = false;
}

void ofxBaseJoint::select()
{
    selected = true;
}

void ofxBaseJoint::unselect()
{
    selected = false;
}

bool ofxBaseJoint::isDragged()
{
    return bDrag;
}

void ofxBaseJoint::setDefaultColors()
{
    fillColor = ofColor(0, 255, 255, 0);
    strokeColor = ofColor(255, 255, 255);
    fillColorSelected = ofColor(255, 255, 0, 0);
    strokeColorSelected = ofColor(255, 0, 0);
}

void ofxBaseJoint::setDefaultProperties()
{
    enabled = true;
    visible = true;
    position = ofVec2f(20.0f, 20.0f);
    clickDistance = ofVec2f(0.0f, 0.0f);
    bDrag = false;
    selected = false;
    strokeWidth = 1.5f;
}