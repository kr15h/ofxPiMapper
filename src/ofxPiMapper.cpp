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

void ofxPiMapper::keyPressed(int key){
	ofKeyEventArgs args;
	args.key = key;
	_application.onKeyPressed(args);
}

void ofxPiMapper::keyReleased(int key){
	ofKeyEventArgs args;
	args.key = key;
	_application.onKeyReleased(args);
}

void ofxPiMapper::mousePressed(int x, int y, int button){
	ofMouseEventArgs args;
	args.x = x;
	args.y = y;
	args.button = button;
	args.type = ofMouseEventArgs::Pressed;
	_application.onMousePressed(args);
}

void ofxPiMapper::mouseReleased(int x, int y, int button){
	ofMouseEventArgs args;
	args.x = x;
	args.y = y;
	args.button = button;
	args.type = ofMouseEventArgs::Released;
	_application.onMouseReleased(args);
}

void ofxPiMapper::mouseDragged(int x, int y, int button){
	ofMouseEventArgs args;
	args.x = x;
	args.y = y;
	args.button = button;
	args.type = ofMouseEventArgs::Dragged;
	_application.onMouseDragged(args);
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
	_application.selectSurface(i);
}

void ofxPiMapper::togglePerspective(){
	_application.togglePerspective();
}

void ofxPiMapper::selectNextSurface(){
	_application.selectNextSurface();
}

void ofxPiMapper::selectPrevSurface(){
	_application.selectPrevSurface();
}

void ofxPiMapper::duplicateSurface(){
	_application.duplicateSurface();
}

void ofxPiMapper::selectNextVertex(){
	_application.selectNextVertex();
}

void ofxPiMapper::selectPrevVertex(){
	_application.selectPrevVertex();
}

void ofxPiMapper::selectVertex(int surface, int vertex){
	_application.selectVertex(surface, vertex);
}

void ofxPiMapper::selectNextTexCoord(){
	_application.selectNextTexCoord();
}

void ofxPiMapper::selectPrevTexCoord(){
	_application.selectPrevTexCoord();
}

void ofxPiMapper::moveLayerUp(){
	_application.moveLayerUp();
}

void ofxPiMapper::moveLayerDown(){
	_application.moveLayerDown();
}

void ofxPiMapper::scaleUp(){
	_application.scaleUp();
}

void ofxPiMapper::scaleDown(){
	_application.scaleDown();
}

void ofxPiMapper::togglePauseForSurface(unsigned int i){
	ofx::piMapper::BaseSource * s =
		_application.getSurfaceManager()->getActivePreset()->getSurfaces().at(i)->getSource();
	if(s->getType() == ofx::piMapper::SourceType::SOURCE_TYPE_VIDEO){
		s->togglePause();
	}
}

void ofxPiMapper::togglePause(){
	_application.togglePause();
}

void ofxPiMapper::moveSelection(ofx::piMapper::Vec3 by){
	_application.moveSelection(by);
}

void ofxPiMapper::createSurface(ofx::piMapper::SurfaceType type){
	_application.createSurface(type);
}

void ofxPiMapper::eraseSurface(int i){
	std::cout << "numSurfaces: " << getNumSurfaces() << ", i: " << i << std::endl;
	if(getNumSurfaces() > 0 && i < getNumSurfaces()){
		_application.eraseSurface(i);
	}
}

void ofxPiMapper::addGridColumn(){
	_application.addGridColumn();
}

void ofxPiMapper::removeGridColumn(){
	_application.removeGridColumn();
}

void ofxPiMapper::addGridRow(){
	_application.addGridRow();
}

void ofxPiMapper::removeGridRow(){
	_application.removeGridRow();
}

void ofxPiMapper::setNextSource(){
	_application.setNextSource();
}

void ofxPiMapper::setFboSource(std::string sourceId){
	_application.setFboSource(sourceId);
}

void ofxPiMapper::setVideoSource(std::string fileName, bool loop){
	_application.setVideoSource(fileName, loop);
}

void ofxPiMapper::setImageSource(std::string fileName){
	_application.setImageSource(fileName);
}

void ofxPiMapper::reboot(){
	_application.reboot();
}

void ofxPiMapper::shutdown(){
	_application.shutdown();
}

void ofxPiMapper::saveProject(){
	_application.saveProject();
}

bool ofxPiMapper::loadProject(std::string filename){
	return _application.loadXmlSettings(filename);
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

int ofxPiMapper::getSelectedSurface(){
	return _application.getSurfaceManager()->getSelectedSurfaceIndex();
}

int ofxPiMapper::getSelectedVertex(){
	return _application.getSurfaceManager()->getSelectedVertexIndex();
}

void ofxPiMapper::setInfoText(std::string text){
	_application.setInfoText(text);
}

void ofxPiMapper::toggleInfo(){
	_application.toggleInfo();
}

void ofxPiMapper::undo(){
	_application.undo();
}

void ofxPiMapper::deselect(){
	_application.deselect();
}

bool ofxPiMapper::toggleShift(){
	return _application.toggleShift();
}

void ofxPiMapper::setMode(ofx::piMapper::Mode m){
	if(m == ofx::piMapper::PRESENTATION_MODE){
		_application.setPresentationMode();
	}else if(m == ofx::piMapper::TEXTURE_MODE){
		_application.setTextureMode();
	}else if(m == ofx::piMapper::MAPPING_MODE){
		_application.setProjectionMode();
	}else if(m == ofx::piMapper::SOURCE_MODE){
		_application.setSourceMode();
	}else{
		ofLogWarning("ofxPiMapper::setMode", "Please specify valid mode");
	}
}

ofx::piMapper::Mode ofxPiMapper::getMode(){
	if(_application.getState() == ofx::piMapper::PresentationMode::instance()){
		return ofx::piMapper::PRESENTATION_MODE;
	}else if(_application.getState() == ofx::piMapper::TextureMappingMode::instance()){
		return ofx::piMapper::TEXTURE_MODE;
	}else if(_application.getState() == ofx::piMapper::ProjectionMappingMode::instance()){
		return ofx::piMapper::MAPPING_MODE;
	}else{
		return ofx::piMapper::SOURCE_MODE;
	}
	return ofx::piMapper::PRESENTATION_MODE;
}

void ofxPiMapper::toggleLayerPanel(){
	_application.toggleLayerPanel();
}
