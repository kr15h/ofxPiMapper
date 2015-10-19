#include "CrossSource.h"

CrossSource::CrossSource() {
    name = "Cross FBO Source";
    allocate(500, 500);
}

void CrossSource::draw() {
    ofClear(0);
    ofSetColor(255, 255, 0, 255);
    ofRect(0, 0, getWidth(), getHeight());
    
    ofSetColor(0, 0, 0, 255);
    ofSetLineWidth(5);
    
    float y = sin( float(ofGetFrameNum()) / 10.0f ) * 100.0f;
    
    ofPoint startPoint = ofPoint(10, y);
    ofPoint endPoint = ofPoint(getWidth() - 10, getHeight() - y);
    ofLine(startPoint, endPoint);
    
    float tempY = startPoint.y;
    startPoint.y = endPoint.y;
    endPoint.y = tempY;
    ofLine(startPoint, endPoint);
}