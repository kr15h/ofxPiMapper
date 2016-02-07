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

	public:
		SurfaceManager();

		void draw();
	
		void addSurface(BaseSurface * surface);
		void removeSelectedSurface();
		void removeSurface();
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
	
		void moveSelectionBy(ofVec2f v);
	
		int size();
	
		ofEvent <int> vertexChangedEvent;
		ofEvent <vector<ofVec3f>> verticesChangedEvent;
		ofEvent <int> surfaceSelectedEvent;
		ofEvent <int> vertexSelectedEvent;

		void onVertexChanged(int & i);
		void onVerticesChanged(vector<ofVec3f> & vertices);
	
	private:
		BaseSurface * selectedSurface;
		ofxXmlSettings xmlSettings;
		MediaServer * mediaServer;
		SurfaceStack _surfaces;
	
		int _selectedVertexIndex;
};

} // namespace piMapper
} // namespace ofx