#pragma once

#include "BaseSurface.h"
#include "TriangleSurface.h"
#include "QuadSurface.h"
#include "SurfaceType.h"
#include "MediaServer.h"
#include "BaseSource.h"
#include "SourceType.h"
#include "SurfaceStack.h"
#include "SurfaceFactory.h"
#include "Vec2.h"

#include "ofEvents.h"
#include "ofxXmlSettings.h"
#include "SettingsLoader.h"

using namespace std;

namespace ofx {
namespace piMapper {

class SurfaceManager {

	public:
		SurfaceManager();

		void draw();
	
		void addSurface(BaseSurface * surface);
		void removeSelectedSurface();
		void removeSurface();
		void removeSurface(int i);
		void deleteSurface(BaseSurface * surface);
		void deselectSurface();
		void saveXmlSettings(std::string fileName);
		void setMediaServer(MediaServer * newMediaServer);
		void clearPresets();
		
		bool loadXmlSettings(std::string fileName);
	
		BaseSurface * getSurface(int index);
		BaseSurface * selectSurface(int index);
		BaseSurface * selectSurface(BaseSurface * surface);
		BaseSurface * selectNextSurface();
		BaseSurface * selectPrevSurface();
		BaseSurface * getSelectedSurface();
	
		// These should trigger an event for the GUI layer to catch
		void selectNextVertex();
		void selectPrevVertex();
		void selectVertex(int i);
	
        void fullscreenSurface();
		void moveSelectionBy(Vec3 v);
		void moveAllSurfacesBy(Vec3 v);
	
		int size();
		int getSelectedVertexIndex();
		int getActivePresetIndex();
		int getSelectedSurfaceIndex();
		unsigned int getNumPresets();
	
		ofEvent <int> vertexChangedEvent;
		ofEvent <std::vector<Vec3>> verticesChangedEvent;
		ofEvent <int> surfaceSelectedEvent;
		ofEvent <int> vertexSelectedEvent;
		ofEvent <int> vertexUnselectedEvent;

		void onVertexChanged(int & i);
		void onVerticesChanged(std::vector<Vec3> & vertices);

		SurfaceStack * getActivePreset();
		SurfaceStack * createPreset();
		SurfaceStack * getPresetAt(unsigned int i);
	
		void setNextPreset();
		void setPreset(unsigned int i);
		void cloneActivePreset();
		void eraseActivePreset();
        void setPresetSourcesActiveState(unsigned int presetIndex, bool state);
	
	private:
		BaseSurface * selectedSurface;
		ofxXmlSettings xmlSettings;
		MediaServer * mediaServer;
	
		int _selectedVertexIndex;
		int _activePresetIndex;
	
		std::vector<SurfaceStack *> _presets;

};

} // namespace piMapper
} // namespace ofx
