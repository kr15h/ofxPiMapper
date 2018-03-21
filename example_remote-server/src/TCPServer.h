#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"

class TCPServer {
public:
	static shared_ptr<TCPServer> instance();

	void setup(int port);
	void update();
	void draw();
	
	void send(int clientID, std::string message);
	
private:
	TCPServer();
	static shared_ptr<TCPServer> _instance;

	ofxTCPServer _tcpServer;
	std::map<int, bool> _tcpConnections;
};
