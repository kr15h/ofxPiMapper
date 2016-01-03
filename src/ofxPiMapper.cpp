#include "ofxPiMapper.h"

ofxPiMapper::ofxPiMapper(){
	bShowInfo = false;
	isSetUp = false;
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
}

void ofxPiMapper::draw(){
	if(!isSetUp){
		return;
	}

	gui.draw();

	if(bShowInfo){
		stringstream ss;
		ss << "There are 4 modes:\n\n";
		ss << " 1. Presentation mode\n";
		ss << " 2. Texture mapping mode\n";
		ss << " 3. Projection mapping mode\n";
		ss << " 4. Source selection mode\n\n";
		ss << "You can switch between the modes by using <1>, <2>, <3> and <4> "
			"keys on the keyboard.\n\n";
		ss << "Press <t> to add new triangle surface\n";
		ss << "Press <q> to add new quad surface\n";
		ss << "Press <s> to save the composition\n";
		ss << "Press <f> to toggle fullscreen\n";
		ss << "Press <i> to hide this message";
		ofDrawBitmapStringHighlight(ss.str(), 10, 20,
									ofColor(0, 0, 0, 100),
									ofColor(255, 255, 255, 200));
	}

	_application->draw();
} // draw

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