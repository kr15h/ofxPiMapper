#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxJSONElement.h"

class TCPClient{
public:
	static shared_ptr<TCPClient> instance();
	
	void setup(string ip, int port);
	void update();
	void draw();
	
	void send(string message);
	
private:
	TCPClient();
	static shared_ptr<TCPClient> _instance;
	
	ofxTCPClient _tcpClient;
};
