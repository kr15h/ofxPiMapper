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
        void addTriangleSurface();
        void addQuadSurface();
        void showInfo() { bShowInfo = true; };
        void hideInfo() { bShowInfo = false; };
        void toggleInfo() { bShowInfo = !bShowInfo; }
    
        ofx::piMapper::CmdManager & getCmdManager();
        ofx::piMapper::SurfaceManagerGui & getGui();
        ofx::piMapper::MediaServer & getMediaServer();
        ofx::piMapper::SurfaceManager & getSurfaceManager();
        ofx::piMapper::CmdManager cmdManager;
        ofx::piMapper::SurfaceManager surfaceManager;
    
    private:
        bool isSetUp;
        bool bShowInfo;
        ofx::piMapper::MediaServer mediaServer;
        ofx::piMapper::SurfaceManagerGui gui;
        ofx::piMapper::Application * _application;
};