#include "CircleJoint.h"

namespace ofx{
namespace piMapper{

CircleJoint::CircleJoint()
{
    setDefaultProperties();
}

void CircleJoint::update()
{
    if (!enabled) return;
}

void CircleJoint::draw()
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

void CircleJoint::setDefaultProperties()
{
    radius = 10.0f;
}

bool CircleJoint::hitTest(ofVec2f pos)
{
    float distance = position.distance(pos);
    if ( distance < radius ) return true;
    else return false;
}

    }}