#include "CircleSource.h"

bool col = true;

void CircleSource::setup(){
	// Give our source a decent name
	name = "Circle Source";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);
	ofSetCircleResolution(50);

	// Genereate rects to be rendered into the FBO
	int numCircles = 10;  // change this to add more or less rects
	for(int i = 0; i < numCircles; i++){
		circlesRadius.push_back(ofRandom(fbo->getHeight()/2));
		circlesSpeeds.push_back((1.0f + ofRandom(2)));
	}
}

// Don't do any drawing here
void CircleSource::update(){
	// Move rects
	for(int i = 0; i < circlesRadius.size(); i++){
		circlesRadius[i] += circlesSpeeds[i];
		if(circlesRadius[i] > fbo->getHeight()/2){
			circlesRadius[i] = fbo->getHeight()/2*(-1);
		}
	}
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void CircleSource::draw(){
	// Fill FBO with our rects
	ofClear(0);
	ofSetColor(255);
	ofSetLineWidth(ofRandom(3));
	ofNoFill();
		for(int i = 0; i < circlesRadius.size(); i++){
			ofDrawCircle(fbo->getHeight()/2,fbo->getHeight()/2,circlesRadius[i]);
		}
}
