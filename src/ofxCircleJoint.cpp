#include "ofxCircleJoint.h"

ofxCircleJoint::ofxCircleJoint()
{
    setDefaultProperties();
}

void ofxCircleJoint::update(ofEventArgs& args)
{
    if (!enabled) return;
}

void ofxCircleJoint::draw(ofEventArgs& args)
{
    if (!visible) return;
    if (!enabled) return;
    
    ofPushStyle();
    ofFill();
    ofSetColor(fillColor);
    ofCircle(position.x, position.y, radius);
    ofNoFill();
    ofSetColor(strokeColor);
    ofCircle(position.x, position.y, radius);
    ofPopStyle();
}

void ofxCircleJoint::setDefaultProperties()
{
    radius = 10.0f;
}

bool ofxCircleJoint::hitTest(ofVec2f pos)
{
    float distance = position.distance(pos);
    if ( distance < radius ) return true;
    else return false;
}