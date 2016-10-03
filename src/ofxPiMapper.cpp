#include "ofxPiMapper.h"

ofxPiMapper::ofxPiMapper(){}

void ofxPiMapper::setup(){
	_application.setup();
}

void ofxPiMapper::update(){
	_application.update();
}

void ofxPiMapper::draw(){
	_application.draw();
}

void ofxPiMapper::registerFboSource(ofx::piMapper::FboSource & fboSource){
	_application.addFboSource(fboSource);
}

void ofxPiMapper::registerFboSource(ofx::piMapper::FboSource * fboSource){
	_application.addFboSource(fboSource);
}

void ofxPiMapper::setActivePreset(unsigned int i){
	_application.getSurfaceManager()->setActivePreset(i);
}

bool ofxPiMapper::loadXmlSettings(string fileName){
	return _application.loadXmlSettings(fileName);
}

unsigned int ofxPiMapper::getNumPresets(){
	return _application.getSurfaceManager()->getNumPresets();
}

unsigned int ofxPiMapper::getActivePresetIndex(){
	return _application.getSurfaceManager()->getActivePresetIndex();
}
