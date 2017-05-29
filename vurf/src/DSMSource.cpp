#include "DSMSource.h"

void DSMSource::setup(){

	cout << "DSMSource::setup..." << endl;

	// Give our source a decent name
	name = "DSM FBO Source";

	//this->dsm = dsm;

	// Allocate our FBO source, decide how big it should be
	//allocate(dsm->grayImage.getWidth(), dsm->grayImage.getHeight());

	// Genereate rects to be rendered into the FBO
	/*int numRects = 20;  // change this to add more or less rects
	for(int i = 0; i < numRects; i++){
		rects.push_back(ofRectangle(0,
									ofRandom(fbo->getHeight()),
									fbo->getWidth(),
									ofRandom(20)));
		rectSpeeds.push_back((1.0f + ofRandom(5)));
	}*/
}

// Don't do any drawing here
void DSMSource::update(){
	// Move rects
	/*for(int i = 0; i < rects.size(); i++){
		rects[i].y += rectSpeeds[i];
		if(rects[i].y > fbo->getHeight()){
			rects[i].y = -rects[i].getHeight();
		}
	}*/
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void DSMSource::draw(){
	// Fill FBO with our rects
	ofClear(0);
	//ofBackground(0);
	/*ofSetColor(255);
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		for(int i = 0; i < rects.size(); i++){
			ofDrawRectangle(rects[i]);
		}
	#else
		for(int i = 0; i < rects.size(); i++){
			ofRect(rects[i]);
		}
	#endif*/

	dsm->grayImage.draw(0,0);	

	//draw(dsm->grayImage); //.getCvImage());

}
