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

#include "PresentationMode.h"
#include "TextureMappingMode.h"
#include "ProjectionMappingMode.h"
#include "SourceSelectionMode.h"

namespace ofx {
namespace piMapper {
	class Application;
}
}

class ofxPiMapper {
	public:
		enum Mode {
			PRESENTATION_MODE,
			TEXTURE_MODE,
			PROJECTION_MODE,
			SOURCE_MODE
		};
	
		ofxPiMapper();

		void setup();
		void update();
		void draw();
	
		void registerFboSource(ofx::piMapper::FboSource & fboSource);
		void registerFboSource(ofx::piMapper::FboSource * fboSource);
		void setActivePreset(unsigned int i);
		void setNextPreset();
		void cloneActivePreset();
		void eraseActivePreset();

		bool loadXmlSettings(string fileName);
	
		unsigned int getNumPresets();
		unsigned int getActivePresetIndex();
	
		Mode getMode();

	private:
		ofx::piMapper::Application _application;
};
