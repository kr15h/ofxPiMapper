#ifndef H_OF_APP
#define H_OF_APP

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public: 
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
};

#endif