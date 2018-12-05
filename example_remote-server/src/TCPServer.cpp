#include "TCPServer.h"

shared_ptr<TCPServer> TCPServer::_instance = 0;

shared_ptr<TCPServer> TCPServer::instance(){
	if(_instance == 0){
		_instance = shared_ptr<TCPServer>(new TCPServer);
	}
	return _instance;
}

TCPServer::TCPServer(){
	std::cout << "TCPServer initialized" << std::endl;
}

void TCPServer::setup(int port){
	_tcpServer.setup(port);
}

void TCPServer::update(){
	int numClients = _tcpServer.getLastID();
	for(auto i = 0; i < numClients; ++i){
		if(_tcpServer.isClientConnected(i)){
			
			// Notify application when new client connects
			if(!_tcpConnections[i]){
				ofxJSONElement json;
				json["ip"] = _tcpServer.getClientIP(i);
				json["port"] = _tcpServer.getClientPort(i);
				json["id"] = i;
				json["event"] = "connected";

				ofMessage message(json.getRawString());
				ofSendMessage(message);
				
				_tcpConnections[i] = true;
			}
			
			// Receive messages
			string rx = _tcpServer.receive(i);
			if(rx.length() > 0){
				ofxJSONElement json;
				bool ok = json.parse(rx);
				
				if(!ok){
					json["ip"] = _tcpServer.getClientIP(i);
					json["port"] = _tcpServer.getClientPort(i);
					json["id"] = i;
					json["event"] = "received";
					json["data"] = rx;
				}
			
				ofMessage message(json.getRawString());
				ofSendMessage(message);
			}
		}else{
		
			// Notify application when client disconnects
			if(_tcpConnections[i]){
				ofxJSONElement json;
				json["ip"] = _tcpServer.getClientIP(i);
				json["port"] = _tcpServer.getClientPort(i);
				json["id"] = i;
				json["event"] = "disconnected";
				
				ofMessage message(json.getRawString());
				ofSendMessage(message);
				
				_tcpConnections[i] = false;
			}
		}
	}
}

void TCPServer::draw(){
	int numClients = _tcpServer.getLastID();
	int clientsConnected = 0;
	for(auto i = 0; i < numClients; ++i){
		if(_tcpServer.isClientConnected(i)){
			ofPushMatrix();
				ofTranslate(10, 10);
				ofPushStyle();
					ofSetColor(0, 255, 0);
					ofDrawRectangle(clientsConnected * 20, 0, 10, 10);
				ofPopStyle();
			ofPopMatrix();
			clientsConnected++;
		}
	}
}

void TCPServer::send(int clientID, std::string message){
	_tcpServer.send(clientID, message);
}

