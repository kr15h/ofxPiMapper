#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "BaseSource.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void update();
  void draw();
  void exit();

  ofxPiMapper piMapper;
  
  // Custom FBO surface variables
  ofImage image;
  ofFbo* fbo;
  ofx::piMapper::BaseSource* fboSource;
  vector<ofRectangle> rects;
  vector<float> rectSpeeds;
};