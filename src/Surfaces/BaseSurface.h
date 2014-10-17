#pragma once

#include "ofMain.h"
#include <string>
#include "BaseSource.h"

using namespace std;

namespace ofx {
namespace piMapper {
class BaseSurface {
 public:
  BaseSurface();
  ~BaseSurface();
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
  //void setTexture(ofTexture* texturePtr);
  void setSource(BaseSource* newSource);
  
  //ofTexture* getTexture();
  //ofTexture* getDefaultTexture();
  BaseSource* getSource();
  BaseSource* getDefaultSource();
  
 protected:
  ofMesh mesh;
  //ofTexture* texture;
  ofTexture defaultTexture;
  BaseSource* source;
  BaseSource* defaultSource;
  
  void createDefaultTexture();
};
}
}