#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	crossSource = new CrossSource();
	customSource = new CustomSource();

	// Create the slide show source.
	slideShowSource = new magSlideShowSource();

	// Create the settings struct for the slide show.

	// Initialize the slide show with our settings.
	// If it fails, initialize from default settings


	// Register our sources:
	piMapper.registerFboSource(crossSource);
	piMapper.registerFboSource(customSource);
	piMapper.registerFboSource(slideShowSource);
	piMapper.setup();

	// Slide show needs to be loaded after piMapper is set up:
	if (!slideShowSource->loadFromXml())
	{
		ofLogNotice("setup") << "loading magSlideShowSource XML settings failed. Initializing from default values";
		magSlideShowSource::Settings sets;
		slideShowSource->initialize(sets);
	}

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();

	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);
    ofSetLogLevel(OF_LOG_VERBOSE);

    slideShowSource->play();
}

void ofApp::update(){
	piMapper.update();
}

void ofApp::draw(){
	piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);
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
