#include "QuadSource.h"

void QuadSource::setup(){
	// Give our source a decent name
	name = "Quad Source";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);

	// Genereate rects to be rendered into the FBO
	int numQuads = 20;  // change this to add more or less rects
	for(int i = 0; i < numQuads; i++){
		float qsize = ofRandom(fbo->getWidth());
		float fbosize = fbo->getWidth();

		quads.push_back(ofRectangle(fbosize/2 - qsize/2,
																fbosize/2 - qsize/2,
																qsize,
																qsize));

		quadSpeeds.push_back((1.0f + ofRandom(5)));
	}
}

// Don't do any drawing here
void QuadSource::update(){
	// Move quads
	for(int i = 0; i < quads.size(); i++){
		quads[i].x -= quadSpeeds[i]/2;
		quads[i].y -= quadSpeeds[i]/2;
		quads[i].width += quadSpeeds[i];
		quads[i].height += quadSpeeds[i];

		if(quads[i].width > fbo->getHeight()){
			quads[i].x = fbo->getWidth()/2;
			quads[i].y = fbo->getWidth()/2;
			quads[i].width = 0.0f;
			quads[i].height = 0.0f;
		}
	}
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void QuadSource::draw(){
	// Fill FBO with our quads
	ofClear(0);
	//ofBackground(0);
	ofNoFill();
	ofSetColor(255);

	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		for(int i = 0; i < quads.size(); i++){
			ofSetLineWidth(ofRandom(5));
			ofDrawRectangle(quads[i]);
		}
	#else
		for(int i = 0; i < quads.size(); i++){
			ofRect(quads[i]);
		}
	#endif
}
