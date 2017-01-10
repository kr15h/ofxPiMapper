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
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
	
		void registerFboSource(ofx::piMapper::FboSource & fboSource);
		void registerFboSource(ofx::piMapper::FboSource * fboSource);
	
		// Application
		void toggleInfo();
	
		// Modes
		void setMode(ofxPiMapper::Mode m);
		ofxPiMapper::Mode getMode();
	
		// Project
		void saveProject();
		bool loadProject(string filename);
	
		// Presets
		unsigned int getNumPresets();
		unsigned int getActivePresetIndex();
		void setPreset(unsigned int i);
		void setNextPreset();
		void cloneActivePreset();
		void eraseActivePreset();
	
		// Surfaces, active preset
		unsigned int getNumSurfaces();
		void selectSurface(int i);
		void selectNextSurface();
		void selectPrevSurface();
		void selectNextVertex();
		void selectPrevVertex();
		void togglePauseForSurface(unsigned int i);
		void moveSelection(ofVec2f by);

	private:
		ofx::piMapper::Application _application;
};
