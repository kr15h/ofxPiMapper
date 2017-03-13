#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "InputHandler.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
	
		void messageReceived(ofMessage & message);
	
		void handleController(ControllerCommand com);

		ofxPiMapper mapper;
};