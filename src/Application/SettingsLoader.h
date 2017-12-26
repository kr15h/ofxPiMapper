#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "SurfaceStack.h"
#include "SurfaceManager.h"
#include "MediaServer.h"
#include "SurfaceFactory.h"
#include "SurfaceType.h"
#include "SourceTypeHelper.h"
#include "Vec2.h"
#include "Vec3.h"

namespace ofx {
namespace piMapper {

class SurfaceManager;

class SettingsLoader {
	public:
		static SettingsLoader * instance();
	
		bool load(SurfaceManager & surfaceManager, MediaServer & mediaServer, std::string fileName);
		bool save(SurfaceManager & surfaceManager, std::string fileName);
		bool create(std::string fileName);
	
		std::string getLastLoadedFilename(){ return _lastLoadedFilename; };
	
	private:
		static SettingsLoader * _instance;
    
        SettingsLoader();
	
		BaseSurface * getTriangleSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getQuadSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getGridWarpSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getHexagonSurface(ofxXmlSettings * xmlSettings);
	
		std::string _lastLoadedFilename;
};

} // namespace piMapper
} // namespace ofx
