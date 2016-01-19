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
		~SurfaceManager();

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
		BaseSurface * getSelectedSurface();
	
		int size();
	
	private:
		BaseSurface * selectedSurface;
		ofxXmlSettings xmlSettings;
		MediaServer * mediaServer;
		SurfaceStack _surfaces;
};

} // namespace piMapper
} // namespace ofx