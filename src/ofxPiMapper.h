#pragma once

#include "ofMain.h"
#include "SurfaceManager.h"
#include "SurfaceManagerGui.h"
#include "MediaServer.h"
#include "FboSource.h"
#include "BaseCmd.h"
#include "CmdManager.h"
#include "RmSurfaceCmd.h"
#include "Application.h"
#include "Info.h"

#define PIMAPPER_DEF_SURFACES_XML_FILE "defaultSurfaces.xml"
#define PIMAPPER_USER_SURFACES_XML_FILE "surfaces.xml"

namespace ofx {
namespace piMapper {
	class Application;
}
}

class ofxPiMapper {

	public:
		ofxPiMapper();

		void setup();
		void draw();
	
		void registerFboSource(ofx::piMapper::FboSource & fboSource);
		bool loadXmlSettings(string fileName);

		ofx::piMapper::CmdManager * getCmdManager();
		ofx::piMapper::SurfaceManagerGui * getGui();
		ofx::piMapper::SurfaceManager * getSurfaceManager();
		ofx::piMapper::Info * getInfo();
	
		// TODO: Redesign ofxPiMapper so that there is a separation between
		// data structures like triangle and quad surfaces and their GUIs.
		// Trianlge and quad surfaces should be still able to draw themselves
		// by using their individual draw methods. The GUI layer would consume
		// triangle and quad surface lists to construct interactive user
		// interface on top of them.

	private:
		bool _setupComplete;
	
		ofx::piMapper::CmdManager * _cmdManager;
		ofx::piMapper::MediaServer * _mediaServer;
		ofx::piMapper::SurfaceManager * _surfaceManager;
		ofx::piMapper::SurfaceManagerGui * _gui;
		ofx::piMapper::Application * _application;
		ofx::piMapper::Info * _info;
};