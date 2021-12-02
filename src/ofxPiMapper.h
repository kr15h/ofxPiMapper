#pragma once

#include "ofEvents.h"
#include "ofLog.h"
#include "FboSource.h"
#include "Application.h"
#include "SurfaceType.h"
#include "Mode.h"
#include "Vec2.h"
#include "Vec3.h"

class ofxPiMapper {
	public:
		ofxPiMapper();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		void registerFboSource(ofx::piMapper::FboSource & fboSource);
		void registerFboSource(ofx::piMapper::FboSource * fboSource);

		// Application
		void setInfoText(std::string text);
		void toggleInfo();
		void undo();
		void deselect();
		bool toggleShift();

		// Modes
		void setMode(ofx::piMapper::Mode m);
		ofx::piMapper::Mode getMode();
	
		// Projection mapping mode only
		void toggleLayerPanel();

		// Project
		void saveProject();
		bool loadProject(std::string filename);

		// Presets
		unsigned int getNumPresets();
		unsigned int getActivePresetIndex();
		void setPreset(unsigned int i);
		void setNextPreset();
		void cloneActivePreset();
		void eraseActivePreset();

		// Surfaces, active preset
		unsigned int getNumSurfaces();
		int getSelectedSurface();
		int getSelectedVertex();
		void selectSurface(int i);
		void togglePerspective();
		void selectNextSurface();
		void selectPrevSurface();
		void duplicateSurface();
		void selectNextVertex();
		void selectPrevVertex();
		void selectVertex(int surface, int vertex);
		void selectNextTexCoord();
		void selectPrevTexCoord();
		void moveLayerUp();
		void moveLayerDown();
		void scaleUp();
		void scaleDown();
		void togglePauseForSurface(unsigned int i);
		void togglePause();
		void moveSelection(ofx::piMapper::Vec3 by);
		void createSurface(ofx::piMapper::SurfaceType type);
		void eraseSurface(int i);
	
		// Specifically for GridWarpSurface
		void addGridColumn();
		void removeGridColumn();
		void addGridRow();
		void removeGridRow();

		// Sources, selected surface
		void setNextSource();
		void setFboSource(std::string sourceId);
		void setVideoSource(std::string fileName, bool loop);
		void setImageSource(std::string fileName);
		void setDrawGui(bool drawGui);

		// System commands
		void reboot();
		void shutdown();

		// video play control
		void restart();
		void pause();
		void resume();

	private:
		ofx::piMapper::Application _application;
};
