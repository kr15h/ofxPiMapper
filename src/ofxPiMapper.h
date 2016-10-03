#pragma once

#include "ofMain.h"
#include "SurfaceManager.h"
#include "MediaServer.h"
#include "FboSource.h"
#include "BaseCmd.h"
#include "CmdManager.h"
#include "RmSurfaceCmd.h"
#include "Application.h"
#include "Info.h"

namespace ofx {
namespace piMapper {
	class Application;
}
}

class ofxPiMapper {

	public:
		ofxPiMapper();

		void setup();
		void update();
		void draw();
	
		void registerFboSource(ofx::piMapper::FboSource & fboSource);
		void registerFboSource(ofx::piMapper::FboSource * fboSource);
		void setActivePreset(unsigned int i);

		bool loadXmlSettings(string fileName);
	
		unsigned int getNumPresets();

	private:
		ofx::piMapper::Application _application;
};
