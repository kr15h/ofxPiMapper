#include "ofxPiMapper.h"

ofxPiMapper::ofxPiMapper(){
	_application = new ofx::piMapper::Application();
}

void ofxPiMapper::setup(){
	_application->setup();
}

void ofxPiMapper::draw(){
	_application->draw();
}

void ofxPiMapper::registerFboSource(ofx::piMapper::FboSource & fboSource){
	_application->addFboSource(fboSource);
}