//#include "CrossSource.h"
#include "UDPSource.h"

UDPSource::UDPSource(){
	name = "UDP FBO Source";
	allocate(500, 500);
	setupNetwork();
}

void UDPSource::setupNetwork(){

	udpConnection.Create();
	udpConnection.Bind(11999);
	udpConnection.SetNonBlocking(true);

}

void UDPSource::update(){
	//cout << "update\n";

	char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;
	if(message!=""){
		cout << "received: " << message << "\n";
		stroke.clear();
		float x,y;
		vector<string> strPoints = ofSplitString(message,"[/p]");
		//cout << "got split size " << strPoints.size() << "\n";
		for(int i=0;i<strPoints.size();i++){
			//cout << "looping over '" <<strPoints[i] << "', i is " << i << "\n";
			vector<string> point = ofSplitString(strPoints[i],"|");
			if (point.size()>1) {
				x=atof(point[0].c_str());
				cout << "x is " << x << "\n";
				y=atof(point[1].c_str());
				cout << "y is " << y << "\n";
				point.clear();
				stroke.push_back(ofPoint(x,y));
			}
			//cout << "looped over " << i << "\n";
		}
	}

	//cout << "left stroke with size " << stroke.size() << "\n";

}

void UDPSource::draw(){
	update();
    	ofFill();
	//ofSetColor(0xFFFFFF);
	//ofRect(0,0,200,30);
	//ofSetColor(0x101010);
	//mono.drawString("UDP Receiver Example ", 10, 20);

	if (stroke.size()>0) {
		cout << "setting colour - " << stroke[0].x << ", " << stroke[0].y << "\n";
		ofSetColor(ofColor(stroke[0].x,stroke[0].y,stroke[1].x+128,255)); //stroke[1].y));
		//ofRect(0,0,stroke[0].x,stroke[0].y);
		ofRect(0,0,800,400);
	}
        ofSetLineWidth(5);

	ofSetColor(255);

	for(int i=1;i<stroke.size();i++){
		cout << "drawing stroke " << stroke[i-1].x << ", ";
		ofLine(stroke[i-1].x * 500,stroke[i-1].y * 500,stroke[i].x * 500,stroke[i].y * 500);
	}

	cout << "draw";

}

/*void UDPSource::draw(){
	ofClear(0);
	ofSetColor(255, 255, 0, 255);
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawRectangle(0, 0, getWidth(), getHeight());
	#else
		ofRect(0, 0, getWidth(), getHeight());
	#endif
	ofSetColor(0, 0, 0, 255);
	ofSetLineWidth(5);

	float y = sin(float(ofGetFrameNum()) / 10.0f) * 100.0f;

	ofPoint startPoint = ofPoint(10, y);
	ofPoint endPoint = ofPoint(getWidth() - 10, getHeight() - y);
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawLine(startPoint, endPoint);
	#else
		ofLine(startPoint, endPoint);
	#endif
	float tempY = startPoint.y;
	startPoint.y = endPoint.y;
	endPoint.y = tempY;
	#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 9) || OF_VERSION_MAJOR > 0
		ofDrawLine(startPoint, endPoint);
	#else
		ofLine(startPoint, endPoint);
	#endif

	update();

}*/
