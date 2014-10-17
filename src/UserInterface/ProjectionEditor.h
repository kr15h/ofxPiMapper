#pragma once

#include "SurfaceManager.h"
#include "CircleJoint.h"

namespace ofx {
namespace piMapper {
class ProjectionEditor {
 public:
  ProjectionEditor();
  ~ProjectionEditor();

  void registerAppEvents();
  void unregisterAppEvents();
  void registerMouseEvents();
  void unregisterMouseEvents();
  void registerKeyEvents();
  void unregisterKeyEvents();

  void enable();
  void disable();

  void update(ofEventArgs& args);
  void draw();
  void mouseDragged(ofMouseEventArgs& args);
  void keyPressed(ofKeyEventArgs& args);
  void keyReleased(ofKeyEventArgs& args);
  void gotMessage(ofMessage& msg);
  void setSurfaceManager(SurfaceManager* newSurfaceManager);
  void clearJoints();
  void createJoints();
  void updateJoints();
  void unselectAllJoints();
  void moveSelectedSurface(ofVec2f by);
  void stopDragJoints();
  void updateVertices();
  void moveSelection(ofVec2f by);
  void setSnapDistance(float newSnapDistance);
  CircleJoint* hitTestJoints(ofVec2f pos);

 private:
  SurfaceManager* surfaceManager;
  vector<CircleJoint*> joints;
  bool bShiftKeyDown;
  float fSnapDistance;

  void drawJoints();
};
}
}