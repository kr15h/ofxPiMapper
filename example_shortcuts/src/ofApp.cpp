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
		mapper.setMode(ofx::piMapper::PRESENTATION_MODE);
	}else if(key == '2'){
		mapper.setMode(ofx::piMapper::MAPPING_MODE);
	}else if(key == '3'){
		mapper.setMode(ofx::piMapper::TEXTURE_MODE);
	}else if(key == '4'){
		mapper.setMode(ofx::piMapper::SOURCE_MODE);
	}else if(key == 'w'){
		mapper.createSurface(ofx::piMapper::QUAD_SURFACE);
	}else if(key == 'e'){
		mapper.createSurface(ofx::piMapper::HEXAGON_SURFACE);
	}else if(key == 'r'){
		mapper.createSurface(ofx::piMapper::GRID_WARP_SURFACE);
	}else if(key == 't'){
		mapper.createSurface(ofx::piMapper::TRIANGLE_SURFACE);
	}else if(key == OF_KEY_BACKSPACE){
		mapper.eraseSurface(mapper.getNumSurfaces() - 1);
	}else if(key == OF_KEY_LEFT){
		mapper.moveSelection(ofVec2f(-20.0f, 0.0f));
	}else if(key == OF_KEY_RIGHT){
		mapper.moveSelection(ofVec2f(20.0f, 0.0f));
	}else if(key == OF_KEY_UP){
		mapper.moveSelection(ofVec2f(0.0f, -20.0f));
	}else if(key == OF_KEY_DOWN){
		mapper.moveSelection(ofVec2f(0.0f, 20.0f));
	}else if(key == 'k'){
		mapper.selectNextSurface();
	}else if(key == 'j'){
		mapper.selectPrevSurface();
	}else if(key == 'v'){
		mapper.setNextSource();
	}else if(key == 'd'){
		mapper.duplicateSurface();
	}else if(key == 'l'){
		if(mapper.getMode() == ofx::piMapper::Mode::MAPPING_MODE){
			mapper.selectNextVertex();
		}else if(mapper.getMode() == ofx::piMapper::Mode::TEXTURE_MODE){
			mapper.selectNextTexCoord();
		}
	}else if(key == 'h'){
		if(mapper.getMode() == ofx::piMapper::Mode::MAPPING_MODE){
			mapper.selectPrevVertex();
		}else if(mapper.getMode() == ofx::piMapper::Mode::TEXTURE_MODE){
			mapper.selectPrevTexCoord();
		}
	}else if(key == 'i'){
		mapper.moveLayerUp();
	}else if(key == 'u'){
		mapper.moveLayerDown();
	}else if(key == 'p'){
		mapper.togglePerspective();
	}else if(key == '+'){
		mapper.scaleUp();
	}else if(key == '-'){
		mapper.scaleDown();
	}else if(key == '\\'){
		mapper.togglePause();
	}else if(key == 'n'){
		string multilineInfoText =
			"Custom ofxPiMapper shortcuts\n\n"
			"Good day user.\n"
			"Shortcuts have been customized.\n"
			"Please make sure to provide your own documentation.";
		mapper.setInfoText(multilineInfoText);
		mapper.toggleInfo();
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
