#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	mapper.setup();
	InputHandler::instance()->initialise();
}

void ofApp::update(){
	mapper.update();
	InputHandler::instance()->update();
}

void ofApp::draw(){
	mapper.draw();
}

void ofApp::keyPressed(int key){
	mapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	mapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	mapper.mousePressed(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	mapper.mouseDragged(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	mapper.mouseReleased(x, y, button);
}
