#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

	// We need to forward key and mouse events to ofxPiMapper.
	// By not doing it we have the opportunity to use ofxPiMapper
	// witout the interface.
	
	void keyPressed(int key);
	void keyReleased(int key);

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	
	// This is our mapper object.
	ofxPiMapper mapper;
};
