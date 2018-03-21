#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	
	isMapperSetup = false;
	
	// Set IP address of your RasPi in data/config.json
	ofxJSONElement json;
	json.open("config.json");
	TCPClient::instance()->setup(json["ip"].asString(), json["port"].asInt());
}

void ofApp::update(){
	TCPClient::instance()->update();
	if(isMapperSetup){
		mapper.update();
	}
}

void ofApp::draw(){
	TCPClient::instance()->draw();
	if(isMapperSetup){
		mapper.draw();
	}
}

// This is where we get configuration from the server part of this.
void ofApp::gotMessage(ofMessage m){
	ofxJSONElement json;
	bool ok = json.parse(m.message);
	if(ok){
		if(json["event"] == "received"){
			std::string buffer = json["data"].asString();
			ofxXmlSettings xml;
			xml.loadFromBuffer(buffer);
			xml.save("ofxpimapper.xml");
			
			mapper.setup();
			isMapperSetup = true;
		}
	}
}

void ofApp::keyPressed(int key){
	if(isMapperSetup){
		mapper.keyPressed(key);
		
		ofxJSONElement json;
		json["event"] = "keyPressed";
		json["key"] = key;
		
		TCPClient::instance()->send(json.getRawString());
	}
}

void ofApp::keyReleased(int key){
	if(isMapperSetup){
		mapper.keyReleased(key);
		
		ofxJSONElement json;
		json["event"] = "keyReleased";
		json["key"] = key;
		
		TCPClient::instance()->send(json.getRawString());
	}
}

void ofApp::mousePressed(int x, int y, int button){
	if(isMapperSetup){
		mapper.mousePressed(x, y, button);
		
		ofxJSONElement json;
		json["event"] = "mousePressed";
		json["x"] = x;
		json["y"] = y;
		json["button"] = button;
		
		TCPClient::instance()->send(json.getRawString());
	}
}

void ofApp::mouseReleased(int x, int y, int button){
	if(isMapperSetup){
		mapper.mouseReleased(x, y, button);
		
		ofxJSONElement json;
		json["event"] = "mouseReleased";
		json["x"] = x;
		json["y"] = y;
		json["button"] = button;
		
		TCPClient::instance()->send(json.getRawString());
	}
}

void ofApp::mouseDragged(int x, int y, int button){
	if(isMapperSetup){
		mapper.mouseDragged(x, y, button);
		
		ofxJSONElement json;
		json["event"] = "mouseDragged";
		json["x"] = x;
		json["y"] = y;
		json["button"] = button;
		
		TCPClient::instance()->send(json.getRawString());
	}
}
