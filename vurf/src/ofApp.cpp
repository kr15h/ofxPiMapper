#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = false;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	crossSource = new CrossSource();
	customSource = new CustomSource();
	customShader = new CustomShader();
	dsmSource = new DSMSource();
	//udpSource = new UDPSource();
	//piMapper.registerFboSource(udpSource);
	piMapper.registerFboSource(crossSource);
	piMapper.registerFboSource(customSource);
	piMapper.registerFboSource(customShader);
	piMapper.registerFboSource(dsmSource);
	piMapper.setup();

	dynamic.setup(&piMapper);

	dsmSource->setDynamic(&dynamic);

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();

	ofSetFullscreen(Settings::instance()->getFullscreen());
}

void ofApp::update(){
	piMapper.update();
	dynamic.update();
}

void ofApp::draw(){
	piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);

	switch(key) {
		case '0':
			piMapper.moveSelection(ofDefaultVec2(0.1f,0.1f));
			cout << "moved\n";
		break;
	}
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}
