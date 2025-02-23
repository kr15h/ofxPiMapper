#include "XSource.h"


XSource::XSource(Display* d, Window win, const std::string& windowName) {
    display = d;
    targetWindow = win;
    name = windowName;
}

void XSource::setup(){

    // Allocate our FBO source, decide how big it should be
    allocate(500, 500); 

    // Generate rects to be rendered into the FBO
    int numRects = 20;  // change this to add more or less rects
    for(int i = 0; i < numRects; i++){
        rects.push_back(ofRectangle(0,
                                    ofRandom(fbo->getHeight()),
                                    fbo->getWidth(),
                                    ofRandom(20)));
        rectSpeeds.push_back((1.0f + ofRandom(5)));
    }
}

// Don't do any drawing here
void XSource::update(){
	// Move rects
	for(int i = 0; i < rects.size(); i++){
		rects[i].y += rectSpeeds[i];
		if(rects[i].y > fbo->getHeight()){
			rects[i].y = -rects[i].getHeight();
		}
	}
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void XSource::draw(){
	// Fill FBO with our rects
	ofClear(0);
	ofSetColor(0);
    for(int i = 0; i < rects.size(); i++){
        ofDrawRectangle(rects[i]);
    }
}
