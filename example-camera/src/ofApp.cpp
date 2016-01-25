#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	cameraSource = new CameraSource();
	piMapper.registerFboSource(*cameraSource);
	piMapper.setup();
}

void ofApp::draw(){
	piMapper.draw();
}