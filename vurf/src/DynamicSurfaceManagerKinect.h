#pragma once
#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"

#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"


/*#include "BaseSurface.h"
#include "TriangleSurface.h"
#include "QuadSurface.h"
#include "SurfaceType.h"
#include "MediaServer.h"
#include "BaseSource.h"
#include "SourceType.h"
#include "SurfaceStack.h"
#include "SurfaceFactory.h"*/

#include "ofEvents.h"
#include "ofxXmlSettings.h"
#include "SettingsLoader.h"

#include "ofxKinect.h"
#include "ofxKinectProjectorToolkit.h"



using namespace std;

//namespace ofx {
//namespace piMapper {

class DynamicSurfaceManagerKinect {

        public:
                DynamicSurfaceManagerKinect();

                void update();
		void updateKinect();

		void setup(ofxPiMapper *setupPiMapper);

    ofxCv::ContourFinder        contourFinder;
    ofxKinectProjectorToolkit   kpt;
    ofxKinect                   kinect;

    ofxCvGrayscaleImage         bgImage;
    ofxCvGrayscaleImage         grayImage;
    ofxCvGrayscaleImage         grayThreshNear;
    ofxCvGrayscaleImage         grayThreshFar;

    ofParameter<float>          nearThreshold;
    ofParameter<float>          farThreshold;
    ofParameter<float>          minArea;
    ofParameter<float>          maxArea;
    ofParameter<float>          threshold;
    ofParameter<float>          persistence;
    ofParameter<float>          maxDistance;




	private:

		ofxPanel                    gui;


		ofxPiMapper *piMapper;

		void setupKinect();

};
