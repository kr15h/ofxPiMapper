// ofxPiMapper
// Author: Krisjanis Rijnieks

// On using prefixes like m or p (mMemberVariable, pMyPointer)
// http://stackoverflow.com/questions/1228161/why-use-prefixes-on-member-variables-in-c-classes

#pragma once

#include "ofMain.h"
#include "SurfaceManager.h"
#include "SurfaceManagerGui.h"
#include "MediaServer.h"
#include "FboSource.h"

#include "BaseCommand.h"
#include "TestCommand.h" // TODO: Remove this line when done testing
#include "TestUndoCommand.h"
#include "CommandManager.h"

#define PIMAPPER_DEF_SURFACES_XML_FILE "defaultSurfaces.xml"
#define PIMAPPER_USER_SURFACES_XML_FILE "surfaces.xml"

class ofxPiMapper{
    
    public:
        ofxPiMapper();
        ~ofxPiMapper();
        
        void setup();
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
        
        // Discussion:
        // Maybe these should be static as this would allow to access them
        // from anywhere within ofxPiMapper.
        ofx::piMapper::MediaServer& getMediaServer();
        ofx::piMapper::SurfaceManager& getSurfaceManager();
       
        // Test first steps of the Command design pattern implementation.
        void testCommand(string name);
        void testUndoableCommand(int increase);
        int undoTestValue;
        ofx::piMapper::CommandManager commandManager;
        ofx::piMapper::SurfaceManager surfaceManager;
    
    private:
        bool isSetUp;
        bool bShowInfo;
        ofx::piMapper::MediaServer mediaServer;

        // Discussion: Here now the GUI points only to surface manager, 
        // maybe it should be as a separate layer?
        ofx::piMapper::SurfaceManagerGui gui;
};