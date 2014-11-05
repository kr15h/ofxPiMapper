#pragma once

#include "ofMain.h"
#include "SurfaceManager.h"
#include "SurfaceManagerGui.h"
#include "MediaServer.h"

#define PIMAPPER_DEF_SURFACES_XML_FILE "defaultSurfaces.xml"
#define PIMAPPER_USER_SURFACES_XML_FILE "surfaces.xml"

class ofxPiMapper {
public:
  ofxPiMapper();
  ~ofxPiMapper();
  
  void setup();
  void draw(); // Called manually to make custom layering possible
  void keyPressed(ofKeyEventArgs& args);
  
  // TODO: Move these methods to SurfaceManager
  void addTriangleSurface();
  void addQuadSurface();
  
  // Toggle help / info
  void showInfo() { bShowInfo = true; };
  void hideInfo() { bShowInfo = false; };
  
  // Getters
  ofx::piMapper::MediaServer& getMediaServer();
  ofx::piMapper::SurfaceManager& getSurfaceManager();
  
private:
  bool isSetUp;
  bool bShowInfo;
  ofx::piMapper::MediaServer mediaServer;
  ofx::piMapper::SurfaceManager surfaceManager;
  ofx::piMapper::SurfaceManagerGui gui;
};