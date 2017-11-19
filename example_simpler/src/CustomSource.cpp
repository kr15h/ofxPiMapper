#include "CustomSource.h"

void CustomSource::setup(){
	// Give our source a decent name
	name = "Custom FBO Source";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);

	// Genereate rects to be rendered into the FBO
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
void CustomSource::update(){
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
void CustomSource::draw(){
	// Fill FBO with our rects
	ofClear(0);
	ofSetColor(255);
    for(int i = 0; i < rects.size(); i++){
        ofDrawRectangle(rects[i]);
    }
}
