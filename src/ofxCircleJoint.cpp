#include "ofxCircleJoint.h"

ofxCircleJoint::ofxCircleJoint()
{
    setDefaultProperties();
}

void ofxCircleJoint::update()
{
    if (!enabled) return;
}

void ofxCircleJoint::draw()
{
    if (!visible) return;
    if (!enabled) return;
    
    ofPushStyle();
    ofFill();
    
    if ( selected ) {
        ofSetColor(fillColorSelected);
    } else {
        ofSetColor(fillColor);
    }
    
    ofCircle(position.x, position.y, radius);
    ofNoFill();
    
    if ( selected ) {
        ofSetColor(strokeColorSelected);
    } else {
        ofSetColor(strokeColor);
    }
    
    ofSetLineWidth(strokeWidth);
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