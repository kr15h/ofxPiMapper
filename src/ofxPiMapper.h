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

#include "BaseSource.h"
#include "SourceType.h"

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
			MAPPING_MODE,
			SOURCE_MODE
		};
	
		ofxPiMapper();

		void setup();
		void update();
		void draw();
	
		void registerFboSource(ofx::piMapper::FboSource & fboSource);
		void registerFboSource(ofx::piMapper::FboSource * fboSource);
	
		// Modes
		void setMode(ofxPiMapper::Mode m);
		ofxPiMapper::Mode getMode();
	
		// Presets
		void setActivePreset(unsigned int i);
		void setNextPreset();
		void cloneActivePreset();
		void eraseActivePreset();
	
		// Toggle play/pause for a surface in the active preset.
		void togglePauseForSurface(unsigned int i);

		bool loadXmlSettings(string fileName);
	
		unsigned int getNumPresets();
		unsigned int getActivePresetIndex();
	
		// Get number of surfaces in the active preset.
		unsigned int getNumSurfaces();

	private:
		ofx::piMapper::Application _application;
};
