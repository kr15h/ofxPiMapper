#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	mapper.setup();
	
	// Set different info text for PocketVJ
	std::string multilineInfoText =
			"Custom ofxPiMapper shortcuts\n\n"
			"Good day user.\n"
			"Shortcuts have been customized.\n"
			"Please make sure to provide your own documentation.";
	mapper.setInfoText(multilineInfoText);
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
		mapper.setMode(ofx::piMapper::TEXTURE_MODE);
	}else if(key == '3'){
		mapper.setMode(ofx::piMapper::MAPPING_MODE);
	}else if(key == '4'){
		mapper.setMode(ofx::piMapper::SOURCE_MODE);
	}else if(key == 'c'){
		mapper.toggleInfo();
	}else if(key == 't'){
		mapper.createSurface(ofx::piMapper::TRIANGLE_SURFACE);
	}else if(key == 'q'){
		mapper.createSurface(ofx::piMapper::QUAD_SURFACE);
	}else if(key == 'r'){
		mapper.createSurface(ofx::piMapper::CIRCLE_SURFACE);
	}else if(key == 'x'){
		mapper.createSurface(ofx::piMapper::HEXAGON_SURFACE);
	}else if(key == 'g'){
		mapper.createSurface(ofx::piMapper::GRID_WARP_SURFACE);
	}else if(key == 'a'){
		mapper.duplicateSurface();
	}else if(key == 'o'){
		mapper.scaleUp();
	}else if(key == 'i'){
		mapper.scaleDown();
	}else if(key == 'p'){
		mapper.togglePerspective();
	}else if(key == 'v'){
		// Add columns
	}else if(key == 'b'){
		// Remove columns
	}else if(key == 'n'){
		// Add rows
	}else if(key == 'm'){
		// Remove rows
	}else if(key == '.'){
		mapper.selectNextSurface();
	}else if(key == ','){
		mapper.selectPrevSurface();
	}else if(key == 'k'){
		mapper.selectNextVertex();
	}else if(key == 'l'){
		mapper.selectPrevVertex();
	}else if(key == 'h'){
		mapper.moveLayerUp();
	}else if(key == 'j'){
		mapper.moveLayerDown();
	}else if(key == 's'){
		mapper.saveProject();
	}else if(key == 'y'){
		// Toggle layer panel
	}else if(key == 'z'){
		mapper.undo();
	}else if(key == 'd'){
		mapper.eraseSurface(mapper.getSelectedSurface());
	}else if(key == 'w'){
		mapper.togglePause();
	}else if(key == '5'){
		mapper.setNextSource();
	}else if(key == '8'){
		mapper.moveSelection(ofx::piMapper::Vec3(0.0f, -1.0f, 0.0f));
	}else if(key == '9'){
		mapper.moveSelection(ofx::piMapper::Vec3(0.0f, 1.0f, 0.0f));
	}else if(key == '7'){
		mapper.moveSelection(ofx::piMapper::Vec3(-1.0f, 0.0f, 0.0f));
	}else if(key == '0'){
		mapper.moveSelection(ofx::piMapper::Vec3(1.0f, 0.0f, 0.0f));
	}
	
	// Make / toggle between shif/unshift (how to capture that with EGL window?)
	
	/*
	rbt	Reboot (Raspberry Pi only)
	sdn	Shutdown (Raspberry Pi only)
	new	Clear composition (remove all surfaces)
	ext	Exit application and return to command line
	*/
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
