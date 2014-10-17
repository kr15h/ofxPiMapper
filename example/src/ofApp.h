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

  void keyPressed(int key);

  void addRandomSurface();
  void addQuadSurface();
  void addSurface();
  void setFboAsSource();

  ofImage image;
  ofx::piMapper::MediaServer mediaServer;
  ofx::piMapper::SurfaceManager surfaceManager;
  ofx::piMapper::SurfaceManagerGui gui;
  bool bShowInfo;
  ofFbo* fbo;
  ofx::piMapper::BaseSource* fboSource;
  vector<ofRectangle> rects;
  vector<float> rectSpeeds;
};