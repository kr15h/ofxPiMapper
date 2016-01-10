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

		void clear();
		void saveXmlSettings(string fileName);
		bool loadXmlSettings(string fileName);
		void setMediaServer(MediaServer * newMediaServer);

		BaseSurface * getSurface(int index);
		int size();
		BaseSurface * selectSurface(int index);
		BaseSurface * selectSurface(BaseSurface * surface);
		BaseSurface * getSelectedSurface();
		void deselectSurface();

	private:
		vector <BaseSurface *> surfaces;
		BaseSurface * selectedSurface;
		ofxXmlSettings xmlSettings;
		MediaServer * mediaServer;
	
		SurfaceStack _surfaces;

};

} // namespace piMapper
} // namespace ofx