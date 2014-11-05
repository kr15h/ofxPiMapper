#include "ofApp.h"

void ofApp::setup() {
  ofBackground(0);
  
  // The ofxPiMapper is being set up automatically before the first
  // ofApp setup call
  piMapper.showInfo(); // The info layer is hidden by default, press <i> to toggle

  // Add our CustomSource to list of fbo sources of the piMapper
  piMapper.getMediaServer().addFboSource(customSource);
}

void ofApp::draw() {
  piMapper.draw();
}