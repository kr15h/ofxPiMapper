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

void ofApp::messageReceived(ofMessage & message){
	ControllerCommand com = (ControllerCommand)ofToInt(message.message);
	handleController(com);
}

/* These values we take into consideration

  ↖ ↑ ↗        y
  ←   →  --  x   b
  ↙ ↓ ↘        a

*/
void ofApp::handleController(ControllerCommand com){
	if(com == ControllerCommand::COMMAND_LEFT){
		mapper.moveSelection(ofVec2f(-5.0f, 0.0f));
	}else if(com == ControllerCommand::COMMAND_RIGHT){
		mapper.moveSelection(ofVec2f(5.0f, 0.0f));
	}else if(com == ControllerCommand::COMMAND_UP){
		mapper.moveSelection(ofVec2f(0.0f, -5.0f));
	}else if(com == ControllerCommand::COMMAND_DOWN){
		mapper.moveSelection(ofVec2f(0.0f, 5.0f));
	}else if(com == ControllerCommand::COMMAND_A){
		mapper.selectNextVertex();
	}else if(com == ControllerCommand::COMMAND_B){
		mapper.selectNextSurface();
	}else if(com == ControllerCommand::COMMAND_X){
		mapper.setMode(ofx::piMapper::Mode::MAPPING_MODE);
	}else if(com == ControllerCommand::COMMAND_Y){
		mapper.setMode(ofx::piMapper::Mode::TEXTURE_MODE);
	}else if(com == ControllerCommand::COMMAND_SELECT){
		mapper.setNextSource();
	}else if(com == ControllerCommand::COMMAND_START){
		mapper.setMode(ofx::piMapper::Mode::PRESENTATION_MODE);
	}
}
