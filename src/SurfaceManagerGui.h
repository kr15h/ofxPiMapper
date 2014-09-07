#pragma once

// I'm starting to think, maybe we should use ofxStateMachine here.
// Would make sense. TODO later.

#include "ofEvents.h"
#include "ofGraphics.h"

#include "SurfaceManager.h"
#include "TextureEditor.h"
#include "ProjectionEditor.h"
#include "SourcesEditor.h"
#include "GuiMode.h"

namespace ofx {
namespace piMapper {
class SurfaceManagerGui {
 public:
  SurfaceManagerGui();
  ~SurfaceManagerGui();

  void registerMouseEvents();
  void unregisterMouseEvents();

  void draw();
  void mousePressed(ofMouseEventArgs& args);
  void mouseReleased(ofMouseEventArgs& args);
  void mouseDragged(ofMouseEventArgs& args);
  void setSurfaceManager(SurfaceManager* newSurfaceManager);
  void setMode(int newGuiMode);
  void drawSelectedSurfaceHighlight();
  void drawSelectedSurfaceTextureHighlight();
  void startDrag();
  void stopDrag();

 private:
  SurfaceManager* surfaceManager;
  TextureEditor textureEditor;
  ProjectionEditor projectionEditor;
  SourcesEditor sourcesEditor;
  int guiMode;
  bool bDrag;
  ofVec2f clickPosition;
};
}
}