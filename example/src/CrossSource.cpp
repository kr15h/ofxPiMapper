#include "CrossSource.h"

CrossSource::CrossSource(){
	name = "Cross FBO Source";
	allocate(500, 500);
}

void CrossSource::draw(){
	ofClear(0);
	ofSetColor(255, 255, 0, 255);
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawRectangle(0, 0, getWidth(), getHeight());
	#else
		ofRect(0, 0, getWidth(), getHeight());
	#endif
	ofSetColor(0, 0, 0, 255);
	ofSetLineWidth(5);

	float y = sin(float(ofGetFrameNum()) / 10.0f) * 100.0f;

	ofPoint startPoint = ofPoint(10, y);
	ofPoint endPoint = ofPoint(getWidth() - 10, getHeight() - y);
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawLine(startPoint, endPoint);
	#else
		ofLine(startPoint, endPoint);
	#endif
	float tempY = startPoint.y;
	startPoint.y = endPoint.y;
	endPoint.y = tempY;
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawLine(startPoint, endPoint);
	#else
		ofLine(startPoint, endPoint);
	#endif
}