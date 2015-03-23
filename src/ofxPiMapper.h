/* ofxPiMapper
 *
 * Description: 
 * Main ofxPiMapper class. Holds instances of all necessary parts of the tool:
 *  - MediaServer
 *  - SurfaceManager
 *  - SurfaceManagerGui (this asks for a different architecture)
 *
 * Author: Krisjanis Rijnieks */

#pragma once

#include "ofMain.h"
#include "SurfaceManager.h"
#include "SurfaceManagerGui.h"
#include "MediaServer.h"
#include "FboSource.h"

#include "Command.h"
#include "TestCommand.h" // TODO: Remove this line when done testing

#define PIMAPPER_DEF_SURFACES_XML_FILE "defaultSurfaces.xml"
#define PIMAPPER_USER_SURFACES_XML_FILE "surfaces.xml"

class ofxPiMapper {
public:
  
  // These are here for adding and removing listeners on
  // contruction and deconstruction
  ofxPiMapper();
  ~ofxPiMapper();
  
  // These are here to adapt to the openFrameworks ways
  void setup();
  void draw(); // Called manually to make custom layering possible
  void keyPressed(ofKeyEventArgs& args);

  // Use this to add custom FBO source
  void addFboSource(ofx::piMapper::FboSource& fboSource);
  
  /* Discussion:
   * Maybe it makes more sense to use create prefix instead of add
   * in addTriangleSurface and so on, so we get createTriangleSurface.
   * TODO: Copy/move these methods to SurfaceManager (not sure) */
  void addTriangleSurface();
  void addQuadSurface();
  
  // Toggle help / info
  void showInfo() { bShowInfo = true; };
  void hideInfo() { bShowInfo = false; };
  
  /* Discussion:
   * Maybe these should be static as this would allow to access them
   * from anywhere within ofxPiMapper. */
  ofx::piMapper::MediaServer& getMediaServer();
  ofx::piMapper::SurfaceManager& getSurfaceManager();
	
	// Test first steps of the Command design pattern implementation.
	void testCommand(string name);
	Command * aTestCommand;
	
private:
  bool isSetUp;
  bool bShowInfo;
  ofx::piMapper::MediaServer mediaServer;
  ofx::piMapper::SurfaceManager surfaceManager;
  
  /* Discussion: Here now the GUI points only to surface manager, 
   * maybe it should be as a separate layer?  */
  ofx::piMapper::SurfaceManagerGui gui;
};