#include "ofxBaseJoint.h"

ofxBaseJoint::ofxBaseJoint()
{
    setDefaultColors();
    setDefaultProperties();
}

ofxBaseJoint::~ofxBaseJoint()
{

}

void ofxBaseJoint::mousePressed(int x, int y, int button)
{
    if ( hitTest(ofVec2f(x, y)) ) {
        selected = true;
        clickDistance = position - ofVec2f(x, y);
        startDrag();
    }
}

void ofxBaseJoint::mouseReleased(int x, int y, int button)
{
    stopDrag();
}

void ofxBaseJoint::mouseDragged(int x, int y, int button)
{
    if ( !dragging ) return;    
    position = ofVec2f(x, y) + clickDistance;
}

void ofxBaseJoint::startDrag()
{
    dragging = true;
}

void ofxBaseJoint::stopDrag()
{
    dragging = false;
}

bool ofxBaseJoint::isDragged()
{
    return dragging;
}

void ofxBaseJoint::setDefaultColors()
{
    fillColor = ofColor(0, 255, 255);
    strokeColor = ofColor(255, 255, 255);
    fillColorSelected = ofColor(255, 255, 0);
    strokeColorSelected = ofColor(255, 0, 0);
}

void ofxBaseJoint::setDefaultProperties()
{
    enabled = true;
    visible = true;
    position = ofVec2f(20.0f, 20.0f);
    clickDistance = ofVec2f(0.0f, 0.0f);
    dragging = false;
    selected = false;
    strokeWidth = 1.5f;
}