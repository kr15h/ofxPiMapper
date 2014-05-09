#include "ofxBaseJoint.h"

ofxBaseJoint::ofxBaseJoint()
{
    setDefaultColors();
    setDefaultProperties();
    registerAppEvents();
    registerMouseEvents();
}

ofxBaseJoint::~ofxBaseJoint()
{
    unregisterAppEvents();
    unregisterMouseEvents();
}

void ofxBaseJoint::mousePressed(ofMouseEventArgs &args)
{
    if ( hitTest(ofVec2f(args.x, args.y)) ) {
        clickDistance = position - ofVec2f(args.x, args.y);
        startDrag();
    }
}

void ofxBaseJoint::mouseReleased(ofMouseEventArgs &args)
{
    stopDrag();
}

void ofxBaseJoint::mouseDragged(ofMouseEventArgs &args)
{
    if ( !dragging ) return;
    position = ofVec2f(args.x, args.y) + clickDistance;
}

void ofxBaseJoint::startDrag()
{
    dragging = true;
}

void ofxBaseJoint::stopDrag()
{
    dragging = false;
}

void ofxBaseJoint::setDefaultColors()
{
    fillColor = ofColor(0,255,255);
    strokeColor = ofColor(255,255,255);
}

void ofxBaseJoint::setDefaultProperties()
{
    enabled = true;
    visible = true;
    position = ofVec2f(20.0f, 20.0f);
    clickDistance = ofVec2f(0.0f, 0.0f);
    dragging = false;
}

void ofxBaseJoint::registerAppEvents()
{
    ofAddListener(ofEvents().update, this, &ofxBaseJoint::update);
    ofAddListener(ofEvents().draw, this, &ofxBaseJoint::draw);
}

void ofxBaseJoint::unregisterAppEvents()
{
    ofRemoveListener(ofEvents().update, this, &ofxBaseJoint::update);
    ofRemoveListener(ofEvents().draw, this, &ofxBaseJoint::draw);
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