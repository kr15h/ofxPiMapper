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
    magSlideShowSource::Settings settings;
    settings.width = 1280;
    settings.height = 720;
    settings.slidesFolderPath = "sources/images";
    settings.transitionDuration = 0;
    settings.slideDuration = 0.5;
    settings.loopType = magSlideShowSource::LoopType::NORMAL;
	settings.resizeOption = magSlide::ResizeOptions::FitProportionally;

	// Initialize the slide show with our settings.
    slideShowSource->initialize(settings);

	// Register our sources:
	piMapper.registerFboSource(crossSource);
	piMapper.registerFboSource(customSource);
	piMapper.registerFboSource(slideShowSource);
	piMapper.setup();

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
