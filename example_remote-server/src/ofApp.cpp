#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	mapper.setup();
	TCPServer::instance()->setup(9999);
	
#ifdef TARGET_RASPBERRY_PI
	ofSetFullscreen(true);
#endif
}

void ofApp::update(){
	mapper.update();
	TCPServer::instance()->update();
}

void ofApp::draw(){
	mapper.draw();
	TCPServer::instance()->draw();
}

// Here is where we process messages received from TCPServer instance
void ofApp::gotMessage(ofMessage m){
	std::cout << m.message << std::endl;
	
	ofxJSONElement json;
	bool ok = json.parse(m.message);
	if(ok){
		if(json["event"].asString() == "connected"){
			// Save Mapper composition and get config as string
			std::cout << "Sending mapper config" << std::endl;
			mapper.saveProject();
			
			ofFile file;
			file.open(ofToDataPath("ofxpimapper.xml"), ofFile::ReadOnly, false);
			ofBuffer buff = file.readToBuffer();
			string text = buff.getText();
			
			TCPServer::instance()->send(json["id"].asInt(), text);
		}
		
		if(json["event"].asString() == "keyPressed"){
			mapper.keyPressed(json["key"].asInt());
		}
		
		if(json["event"].asString() == "keyReleased"){
			mapper.keyReleased(json["key"].asInt());
		}
		
		if(json["event"].asString() == "mousePressed"){
			mapper.mousePressed(json["x"].asInt(), json["y"].asInt(), json["button"].asInt());
		}
		
		if(json["event"].asString() == "mouseReleased"){
			mapper.mouseReleased(json["x"].asInt(), json["y"].asInt(), json["button"].asInt());
		}
		
		if(json["event"].asString() == "mouseDragged"){
			mapper.mouseDragged(json["x"].asInt(), json["y"].asInt(), json["button"].asInt());
		}
	}
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

void ofApp::mouseReleased(int x, int y, int button){
	mapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	mapper.mouseDragged(x, y, button);
}

