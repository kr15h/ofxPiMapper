#ifndef H_OFX_BASE_SURFACE
#define H_OFX_BASE_SURFACE

#include "ofMain.h"

class ofxBaseSurface
{
public:
    virtual void setup(){};
    virtual void draw(){};
    
protected:
    ofMesh mesh;
    ofTexture* texture;
};

#endif