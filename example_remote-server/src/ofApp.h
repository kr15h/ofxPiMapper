#pragma once

#include "ofMain.h"
#include "TCPServer.h"
#include "ofxPiMapper.h"
#include "ofxJSONElement.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void gotMessage(ofMessage m);
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	
	ofxPiMapper mapper;
};
