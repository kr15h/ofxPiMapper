#include "TCPClient.h"

shared_ptr<TCPClient> TCPClient::_instance = 0;

shared_ptr<TCPClient> TCPClient::instance(){
	if(_instance == 0){
		_instance = shared_ptr<TCPClient>(new TCPClient);
	}
	return _instance;
}

TCPClient::TCPClient(){
	
}

void TCPClient::setup(string ip, int port){
	_tcpClient.setup(ip, port);
}

void TCPClient::update(){
	if(_tcpClient.isConnected()){
		string rx = _tcpClient.receive();
		if(rx.length() > 0){
			ofxJSONElement json;
			json["event"] = "received";
			json["data"] = rx;
			
			ofMessage m(json.getRawString());
			ofSendMessage(m);
		}
	}
}

void TCPClient::draw(){
	if(_tcpClient.isConnected()){
		ofSetColor(0, 255, 0);
		ofPushMatrix();
		ofTranslate(10, 10);
		ofDrawRectangle(0, 0, 10, 10);
		ofPopMatrix();
	}
}

void TCPClient::send(string message){
	_tcpClient.send(message);
}
