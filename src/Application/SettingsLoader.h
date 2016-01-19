#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "SurfaceStack.h"
#include "MediaServer.h"
#include "SurfaceFactory.h"
#include "SurfaceType.h"

namespace ofx {
namespace piMapper {

class SettingsLoader {
	public:
		static SettingsLoader * instance();
	
		bool load(SurfaceStack & surfaces, MediaServer & mediaServer, string fileName);
		bool save(SurfaceStack & surfaces, string fileName);
	
	private:
		static SettingsLoader * _instance;
	
		BaseSurface * getTriangleSurface(ofxXmlSettings * xmlSettings);
		BaseSurface * getQuadSurface(ofxXmlSettings * xmlSettings);
};

}
}