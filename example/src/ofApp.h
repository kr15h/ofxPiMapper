#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"

class ofApp : public ofBaseApp
{
public: 
	void setup();
	void update();
	void draw();
    void exit();

	void keyPressed(int key);
    
    void addRandomSurface();
    void addQuadSurface();
    void addSurface();
    void setFboAsTexture();
    
    ofImage image;
    ofx::piMapper::SurfaceManager surfaceManager;
    ofx::piMapper::SurfaceManagerGui gui;
    bool bShowInfo;
    ofFbo* fbo;    
    vector<ofRectangle> rects;
    vector<float> rectSpeeds;
};