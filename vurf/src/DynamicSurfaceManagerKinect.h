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

#include "CustomContourFinder.h"

using namespace std;

//namespace ofx {
//namespace piMapper {

class DynamicSurfaceManagerKinect {

        public:
                DynamicSurfaceManagerKinect();

                void update();
		void updateKinect();

		void setup(ofxPiMapper *setupPiMapper);

		int getDynamicSurfaceIndex(int label);

    ofxCv::CustomContourFinder        contourFinder;

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

		const static int MAX_VERTEX = 6;
		const static int MAX_DYNAMIC_SURFACES = 16;
		const static int MAX_BLOB_AGE = 50.0f;
                int label_map[MAX_DYNAMIC_SURFACES] = {}; //-1,-1,-1,-1,-1,-1,-1,-1};
                double label_map_lastused[MAX_DYNAMIC_SURFACES] = {}; //{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f}; 

		ofxPiMapper *piMapper;

		void setupKinect();

		void gcSurfaces();

};
