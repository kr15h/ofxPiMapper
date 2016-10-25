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

void ofxPiMapper::setPreset(unsigned int i){
	_application.setPreset(i);
}

void ofxPiMapper::setNextPreset(){
	_application.setNextPreset();
}

void ofxPiMapper::cloneActivePreset(){
	_application.getSurfaceManager()->deselectSurface();
	_application.getSurfaceManager()->cloneActivePreset();
}

void ofxPiMapper::eraseActivePreset(){
	_application.getSurfaceManager()->deselectSurface();
	_application.getSurfaceManager()->eraseActivePreset();
}

void ofxPiMapper::selectSurface(int i){
	_application.getState()->selectSurface(&_application, i);
}

void ofxPiMapper::selectNextSurface(){
	_application.getState()->selectNextSurface(&_application);
}

void ofxPiMapper::selectPrevSurface(){
	_application.getState()->selectPrevSurface(&_application);
}

void ofxPiMapper::togglePauseForSurface(unsigned int i){
	ofx::piMapper::BaseSource * s =
		_application.getSurfaceManager()->getActivePreset()->getSurfaces().at(i)->getSource();
	if(s->getType() == ofx::piMapper::SourceType::SOURCE_TYPE_VIDEO){
		s->togglePause();
	}
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

unsigned int ofxPiMapper::getNumSurfaces(){
	return _application.getSurfaceManager()->getActivePreset()->getSurfaces().size();
}

void ofxPiMapper::setMode(ofxPiMapper::Mode m){
	if(m == PRESENTATION_MODE){
		_application.setPresentationMode();
	}else if(m == TEXTURE_MODE){
		_application.setTextureMode();
	}else if(m == MAPPING_MODE){
		_application.setProjectionMode();
	}else if(m == SOURCE_MODE){
		_application.setSourceMode();
	}else{
		ofLogWarning("ofxPiMapper::setMode", "Please specify valid mode");
	}
}

ofxPiMapper::Mode ofxPiMapper::getMode(){
	if(_application.getState() == ofx::piMapper::PresentationMode::instance()){
		return PRESENTATION_MODE;
	}else if(_application.getState() == ofx::piMapper::TextureMappingMode::instance()){
		return TEXTURE_MODE;
	}else if(_application.getState() == ofx::piMapper::ProjectionMappingMode::instance()){
		return MAPPING_MODE;
	}else{
		return SOURCE_MODE;
	}
	return PRESENTATION_MODE;
}
