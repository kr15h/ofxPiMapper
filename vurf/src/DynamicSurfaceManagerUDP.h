#pragma once
#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
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

#include "ofxNetwork.h"


using namespace std;

//namespace ofx {
//namespace piMapper {

class DynamicSurfaceManagerUDP {

        public:
                DynamicSurfaceManagerUDP();

                void update();

		void setup(ofxPiMapper *setupPiMapper);

		void setupNetwork();

                ofxUDPManager udpConnection;

	private:

		ofxPiMapper *piMapper;

};
