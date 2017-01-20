#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	mapper.setup();
}

void ofApp::update(){
	mapper.update();
}

void ofApp::draw(){
	mapper.draw();
}

void ofApp::keyPressed(int key){
	if(key == '1'){
		mapper.setMode(ofxPiMapper::PRESENTATION_MODE);
	}else if(key == '2'){
		mapper.setMode(ofxPiMapper::MAPPING_MODE);
	}else if(key == '3'){
		mapper.setMode(ofxPiMapper::TEXTURE_MODE);
	}else if(key == '4'){
		mapper.setMode(ofxPiMapper::SOURCE_MODE);
	}else if(key == 'w'){
		mapper.createSurface(ofx::piMapper::QUAD_SURFACE);
	}else if(key == 'e'){
		mapper.createSurface(ofx::piMapper::HEXAGON_SURFACE);
	}else if(key == 'r'){
		mapper.createSurface(ofx::piMapper::GRID_WARP_SURFACE);
	}else if(key == 't'){
		mapper.createSurface(ofx::piMapper::TRIANGLE_SURFACE);
	}else{
		mapper.keyPressed(key);
	}
}

void ofApp::keyReleased(int key){
	mapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	mapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	mapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	mapper.mouseDragged(x, y, button);
}
