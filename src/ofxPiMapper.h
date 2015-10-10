#pragma once

#include "ofMain.h"
#include "SurfaceManager.h"
#include "SurfaceManagerGui.h"
#include "MediaServer.h"
#include "FboSource.h"

// Command design pattern includes
#include "BaseCmd.h"
#include "CmdManager.h"
#include "RmSurfaceCmd.h"

// Main view with state design pattern
#include "Application.h" // Main application entry point

#define PIMAPPER_DEF_SURFACES_XML_FILE "defaultSurfaces.xml"
#define PIMAPPER_USER_SURFACES_XML_FILE "surfaces.xml"

namespace ofx {
    namespace piMapper {
        class Application;
    }
}

class ofxPiMapper{
    
    public:
        ofxPiMapper();
        ~ofxPiMapper();
        
        void setup();
        void stateSetup();
        void draw();
        void keyPressed(ofKeyEventArgs& args);
        
        void addFboSource(ofx::piMapper::FboSource& fboSource);
        
        // Discussion:
        // Maybe it makes more sense to use create prefix instead of add
        // in addTriangleSurface and so on, so we get createTriangleSurface.
        // TODO: Copy/move these methods to SurfaceManager (not sure)
        void addTriangleSurface();
        void addQuadSurface();
        
        // Toggle help / info
        void showInfo() { bShowInfo = true; };
        void hideInfo() { bShowInfo = false; };
    
        // Getters
        ofx::piMapper::CmdManager & getCmdManager();
        ofx::piMapper::SurfaceManagerGui & getGui();
        
        // Discussion:
        // Maybe these should be static as this would allow to access them
        // from anywhere within ofxPiMapper.
        ofx::piMapper::MediaServer& getMediaServer();
        ofx::piMapper::SurfaceManager& getSurfaceManager();
    
        ofx::piMapper::CmdManager cmdManager;
        ofx::piMapper::SurfaceManager surfaceManager;
    
    private:
        bool isSetUp;
        bool bShowInfo;
        ofx::piMapper::MediaServer mediaServer;

        // Discussion: Here now the GUI points only to surface manager, 
        // maybe it should be as a separate layer?
        ofx::piMapper::SurfaceManagerGui gui;
    
    
        ofx::piMapper::Application * _application;
};