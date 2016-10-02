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

#include "ofEvents.h"
#include "ofxXmlSettings.h"
#include "SettingsLoader.h"

using namespace std;

namespace ofx {
namespace piMapper {

class SurfaceManager {

	/* TODO: Add presets.
	 * This would be solved by adding multiple SurfaceStack instances. Depending on selected
	 * preset, it would draw and operate on a a specific surface stack. SurfaceManager would
	 * become kind of a state machine.
	 */

	public:
		SurfaceManager();

		void draw();
	
		void addSurface(BaseSurface * surface);
		void removeSelectedSurface();
		void removeSurface();
		void deleteSurface(BaseSurface * surface);
		void deselectSurface();
		void saveXmlSettings(string fileName);
		void setMediaServer(MediaServer * newMediaServer);
		void clear();
		
		bool loadXmlSettings(string fileName);
	
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
	
		void moveSelectionBy(ofVec2f v);
		void moveAllSurfacesBy(ofVec2f v);
	
		int size();
		int getSelectedVertexIndex();
		int getActivePresetIndex();
	
		ofEvent <int> vertexChangedEvent;
		ofEvent <vector<ofVec3f>> verticesChangedEvent;
		ofEvent <int> surfaceSelectedEvent;
		ofEvent <int> vertexSelectedEvent;
		ofEvent <int> vertexUnselectedEvent;

		void onVertexChanged(int & i);
		void onVerticesChanged(vector<ofVec3f> & vertices);
	
		SurfaceStack * getActivePreset();
		SurfaceStack * createPreset();
	
		void setNextPreset();
	
	private:
		BaseSurface * selectedSurface;
		ofxXmlSettings xmlSettings;
		MediaServer * mediaServer;
	
		int _selectedVertexIndex;
		int _activePresetIndex;
	
		vector <SurfaceStack *> _presets;
	
	
};

} // namespace piMapper
} // namespace ofx