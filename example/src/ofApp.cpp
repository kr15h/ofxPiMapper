#include "ofApp.h"

void ofApp::setup() {
  
  // The ofxPiMapper is being set up automatically before the first
  // ofApp setup call
  piMapper.showInfo(); // The info layer is hidden by default, press <i> to toggle
  
  // Create our custom FBO
  fbo = new ofFbo();
  fbo->allocate(500, 500);
  fboSource = new ofx::piMapper::BaseSource(&fbo->getTextureReference());
  
  // Assign the FBO's texture to one of the surfaces ofxPiMapper has created
  piMapper.getSurfaceManager().getSurface(0)->setSource(fboSource);

  // Genereate rects to be rendered into the FBO
  int numRects = 20;  // change this to add more or less rects
  for (int i = 0; i < numRects; i++) {
    rects.push_back(ofRectangle(0, ofRandom(fbo->getHeight()), fbo->getWidth(),
                                ofRandom(20)));
    rectSpeeds.push_back((1.0f + ofRandom(5)));
  }
}

void ofApp::update() {
  
  // Move rects
  for (int i = 0; i < rects.size(); i++) {
    rects[i].y += rectSpeeds[i];
    if (rects[i].y > fbo->getHeight()) {
      rects[i].y = -rects[i].getHeight();
    }
  }

  // Fill FBO with our rects
  fbo->begin();
  ofClear(0);
  ofBackground(0);
  ofSetColor(255);
  for (int i = 0; i < rects.size(); i++) {
    ofRect(rects[i]);
  }
  fbo->end();
}

void ofApp::draw() {
  piMapper.draw();
}

void ofApp::exit() {
  delete fbo;
}