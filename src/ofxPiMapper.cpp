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

void ofxPiMapper::setNextPreset(){
	_application.getSurfaceManager()->deselectSurface();
	_application.getSurfaceManager()->setNextPreset();
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

ofxPiMapper::Mode ofxPiMapper::getMode(){
	if(_application.getState() == ofx::piMapper::PresentationMode::instance()){
		return PRESENTATION_MODE;
	}else if(_application.getState() == ofx::piMapper::TextureMappingMode::instance()){
		return TEXTURE_MODE;
	}else if(_application.getState() == ofx::piMapper::ProjectionMappingMode::instance()){
		return PROJECTION_MODE;
	}else{
		return SOURCE_MODE;
	}
	return PRESENTATION_MODE;
}
