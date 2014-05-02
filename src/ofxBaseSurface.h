#ifndef H_OFX_BASE_SURFACE
#define H_OFX_BASE_SURFACE

#include "ofMain.h"

class ofxBaseSurface
{
public:
    ofxBaseSurface();
    virtual void setup(){};
    virtual void draw(){};
    virtual void setVertex(int index, ofVec2f p){};
    virtual void setTexCoord(int index, ofVec2f t){};
    
protected:
    ofMesh mesh;
    ofTexture* texture;
    ofTexture defaultTexture;
    
    void createDefaultTexture();
};

#endif