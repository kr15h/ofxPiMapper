#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "FboSource.h"

class UDPSource : public ofx::piMapper::FboSource {
	public:
		UDPSource();

		void draw();
		void setupNetwork();
		void update();

                ofxUDPManager udpConnection;

                vector<ofPoint> stroke;

};


