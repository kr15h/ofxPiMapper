#pragma once

#include "ofMain.h"
#include "BaseSurface.h"
#include "SurfaceType.h"

namespace ofx {
namespace piMapper {
class QuadSurface : public BaseSurface {
 public:
  QuadSurface();
  ~QuadSurface();

  void setup();

  void setup(ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f p4, ofVec2f t1,
             ofVec2f t2, ofVec2f t3, ofVec2f t4, BaseSource* newSource);

  void draw();
  void setVertex(int index, ofVec2f p);
  void setTexCoord(int index, ofVec2f t);
  void moveBy(ofVec2f v);

  int getType();
  bool hitTest(ofVec2f p);
  ofVec2f getVertex(int index);
  ofVec2f getTexCoord(int index);
  ofPolyline getHitArea();
  ofPolyline getTextureHitArea();
  vector<ofVec3f>& getVertices();
  vector<ofVec2f>& getTexCoords();

 private:
  void calculate4dTextureCoords();
  GLfloat quadVertices[12];
  GLubyte quadIndices[6];
  GLfloat quadTexCoordinates[16];
};
}
}