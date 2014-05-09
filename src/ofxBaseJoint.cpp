#include "ofxBaseJoint.h"

ofxBaseJoint::ofxBaseJoint()
{
    registerMouseEvents();
}

ofxBaseJoint::~ofxBaseJoint()
{
    unregisterMouseEvents();
}

void ofxBaseJoint::registerMouseEvents()
{
    ofAddListener(ofEvents().mousePressed, this, &ofxBaseJoint::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxBaseJoint::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this, &ofxBaseJoint::mouseDragged);
}

void ofxBaseJoint::unregisterMouseEvents()
{
    ofRemoveListener(ofEvents().mousePressed, this, &ofxBaseJoint::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxBaseJoint::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxBaseJoint::mouseDragged);
}