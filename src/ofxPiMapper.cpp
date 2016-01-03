#include "ofxPiMapper.h"

ofxPiMapper::ofxPiMapper(){
	bShowInfo = false;
	isSetUp = false;
	_info = 0;
}

void ofxPiMapper::setup(){
	ofLogNotice("ofxPiMapper") << "Setting up...";

	surfaceManager.setMediaServer(&mediaServer);
	gui.setMediaServer(&mediaServer);
	gui.setCmdManager(&cmdManager);

	if(!loadXmlSettings(PIMAPPER_USER_SURFACES_XML_FILE)){
		ofLogWarning("ofxPiMapper::setup()") << "Failed to load user settings, go with default" << endl;
		if(!loadXmlSettings(PIMAPPER_DEF_SURFACES_XML_FILE)){
			ofLogError("ofxPiMapper::setup()") << "Failed to load default settings, exit" << endl;
			ofExit(EXIT_FAILURE);
		}
	}

	gui.setSurfaceManager(&surfaceManager);
	isSetUp = true;
	ofLogNotice("ofxPiMapper") << "Done setting up";
	_application = new ofx::piMapper::Application(this);
	_info = new ofx::piMapper::Info();
}

void ofxPiMapper::draw(){
	if(!isSetUp){
		return;
	}
	gui.draw();
	_application->draw();
	_info->draw();
}

void ofxPiMapper::registerFboSource(ofx::piMapper::FboSource & fboSource){
	mediaServer.addFboSource(fboSource);
}

bool ofxPiMapper::loadXmlSettings(string fileName){
	if(!ofFile::doesFileExist(fileName)){
		ofLogError("ofxPiMapper::loadXmlSettings()") << fileName << " does not exist";
		return false;
	}
	if(!surfaceManager.loadXmlSettings(fileName)){
		ofLogError("ofxPiMapper::loadXmlSettings()") << "Failed to load " << fileName << endl;
		return false;
	}
	return true;
}

ofx::piMapper::CmdManager & ofxPiMapper::getCmdManager(){
	return cmdManager;
}

ofx::piMapper::SurfaceManagerGui & ofxPiMapper::getGui(){
	return gui;
}

ofx::piMapper::MediaServer & ofxPiMapper::getMediaServer(){
	return mediaServer;
}

ofx::piMapper::SurfaceManager & ofxPiMapper::getSurfaceManager(){
	return surfaceManager;
}

ofx::piMapper::Info * ofxPiMapper::getInfo(){
	return _info;
}