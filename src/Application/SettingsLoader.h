#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "SurfaceStack.h"
#include "SurfaceManager.h"
#include "MediaServer.h"
#include "SurfaceFactory.h"
#include "SurfaceType.h"
#include "SourceTypeHelper.h"

namespace ofx {
namespace piMapper {

class SurfaceManager;

class SettingsLoader {
	public:
		static SettingsLoader * instance();
	
		bool load(SurfaceManager & surfaceManager, MediaServer & mediaServer, string fileName);
		bool save(SurfaceManager & surfaceManager, string fileName);
		bool create(string fileName);
	
		string getLastLoadedFilename(){ return _lastLoadedFilename; };
	
	private:
		static SettingsLoader * _instance;
    
        SettingsLoader();
	
		BaseSurface * getTriangleSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getQuadSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getGridWarpSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getHexagonSurface(ofxXmlSettings * xmlSettings);
	
		string _lastLoadedFilename;
};

} // namespace piMapper
} // namespace ofx
