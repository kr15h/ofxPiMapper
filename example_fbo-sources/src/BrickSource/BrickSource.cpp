#include "BrickSource.h"

void BrickSource::setup(){
	// Give our source a decent name
	name = "Brick Source";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);
	ofSetFrameRate(60);

	// Genereate rects to be rendered into the FBO
	int numX = 21;
	int numY = 21;  // change this to add more or less rects
	int motar = 4;
	int brickLength = 20;
	int brickWidth = 20;
	int counter = 0;
	for(int k = 0; k < numY;k++){
		for(int i = 0; i < numX; i++){

			bricks.push_back(ofRectangle(i*(brickLength + motar),
																	k*(brickWidth + motar),
																	brickLength,
																	brickWidth));
			brickColor.push_back(ofRandom(0, 220));
		}
	}
}

// Don't do any drawing here
void BrickSource::update(){
	if (ofGetFrameNum()%30 == 0) {
		for(int i = 0; i < bricks.size(); i++){
		 brickColor[i] = ofRandom(0, 220);
	 }
	}	// Move quads
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void BrickSource::draw(){
	// Fill FBO with our quads
	ofClear(0);
	//ofBackground(0);
	ofFill();

		for(int i = 0; i < bricks.size(); i++){
			//ofSetLineWidth(ofRandom(5));
			ofSetColor(brickColor[i]);
			ofDrawRectangle(bricks[i]);
		}
}
