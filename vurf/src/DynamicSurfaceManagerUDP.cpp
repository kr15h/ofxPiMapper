#include "DynamicSurfaceManagerUDP.h"

DynamicSurfaceManagerUDP::DynamicSurfaceManagerUDP(){
}

void DynamicSurfaceManagerUDP::update() {
	// get info from UDP socket
        char udpMessage[100000];
        udpConnection.Receive(udpMessage,100000);
        string message=udpMessage;
        //message += "..blah..";
        //message = "blah";

        vector<ofPoint> stroke;

        if(message!=""){
        	cout << "received: " << message << "\n";
		stroke.clear();
		//float x,y;///;,width,height;

        	// and parse it into objects and coordinates
        	vector<string> strPoints = ofSplitString(message,"[/p]");
                //cout << "got split size " << strPoints.size() << "\n";
                for(int i=0;i<strPoints.size();i++){
                        //cout << "looping over '" <<strPoints[i] << "', i is " << i << "\n";
                        vector<string> strCoord = ofSplitString(strPoints[i],"|");
			//cout << "got vector split size " << strCoord.size() << endl;
                        if (strCoord.size()>0) {
				for (int n=0;n<strCoord.size();n++) {
					float x,y;
					vector<string> point = ofSplitString(strCoord[n], ",");
					//cout << "got coord split size " << point.size() << endl;
                                	x=atof(point[0].c_str());
	                                cout << "x is " << x << ",";
	                                y=atof(point[1].c_str());
	                                cout << "y is " << y << "\n";
					stroke.push_back(ofPoint(x,y));
	
	                                point.clear();
	                        }
			}
                        //cout << "looped over " << i << "\n";
                }
		strPoints.clear();
        }

	// assign objects to Surfaces 

	// and update surface coordinates

	if (stroke.size()>1) {
		//cout << "scaling to " << stroke[0].x/500 << "\n";
		//piMapper->getApp().getSurfaceManager()->getSurface(1);//->setVertex(0, ofDefaultVec{$1}(stroke[0].x, stroke[0].y)); //joints[i]->position)

		// convert from x,y,width,height to vertices
		vector<ofDefaultVec3> vs;
		vs.push_back(ofDefaultVec2(stroke[0].x, 		stroke[0].y));
		vs.push_back(ofDefaultVec2(stroke[0].x + stroke[1].x, stroke[0].y));
		vs.push_back(ofDefaultVec2(stroke[0].x + stroke[1].x, stroke[0].y + stroke[1].y));
		vs.push_back(ofDefaultVec2(stroke[0].x, 		stroke[0].y + stroke[1].y));

		int surf_index = 0;
		try {	
			piMapper->getApp().getSurfaceManager()->getSurface(surf_index)->setVertices(vs);
		} catch (std::runtime_error& e) {
			cout << "Caught exception updating coordinates for surface #" << surf_index << ": " << e.what() << "\n";
		}
		//ofVec4f(stroke[0].x,stroke[0].x,stroke[1].x,stroke[1].y));
		//scaleTo(stroke[0].x/500);
		//piMapper.getApp()-;
	}

}

void DynamicSurfaceManagerUDP::setupNetwork(){

        udpConnection.Create();
        udpConnection.Bind(11999);
        udpConnection.SetNonBlocking(true);

}


void DynamicSurfaceManagerUDP::setup (ofxPiMapper *setupPiMapper) {
	cout << "DynamicSurfaceManagerUDP::setup\n";

	piMapper = setupPiMapper;

	// setup UDP receiver
	setupNetwork();
	// setup bank of Surfaces for using as dynamic surfaces

        //exit(0);      // for checking output
}

