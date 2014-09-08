#pragma once

#include "ofMain.h"
#include <string>

using namespace std;

namespace ofx {
namespace piMapper {
class BaseSurface {
 public:
  BaseSurface();
  virtual void setup() {};
  virtual void draw() {};
  virtual void setVertex(int index, ofVec2f p) {};
  virtual void setTexCoord(int index, ofVec2f t) {};
  virtual void moveBy(ofVec2f v) {};
  virtual int getType() {};
  virtual bool hitTest(ofVec2f p) {};
  virtual ofPolyline getHitArea() {};
  virtual ofPolyline getTextureHitArea() {};
  virtual vector<ofVec3f>& getVertices() {};
  virtual vector<ofVec2f>& getTexCoords() {};

  // Draws a texture using ofMesh
  void drawTexture(ofVec2f position);
  void setTexture(ofTexture* texturePtr);

  ofTexture* getTexture();
  ofTexture* getDefaultTexture();

 protected:
  ofMesh mesh;
  ofTexture* texture;
  ofTexture defaultTexture;

  void createDefaultTexture();
};
}
}