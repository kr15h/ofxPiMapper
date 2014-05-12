#ifndef H_OFX_SURFACE_MANAGER
#define H_OFX_SURFACE_MANAGER

/*
 Used ofxStateMachine by Neil Mendoza as example for this part of the addon.
 https://github.com/neilmendoza/ofxStateMachine
 */

#include "ofxBaseSurface.h"
#include "ofxTriangleSurface.h"
#include "ofxSurfaceType.h"

using namespace std;

class ofxSurfaceManager
{
public:
    ofxSurfaceManager();
    ~ofxSurfaceManager();
    
    void draw();
    void addSurface(int surfaceType);
    ofxBaseSurface* getSurface(int index);
    int size();
    
private:
    vector<ofxBaseSurface*> surfaces;
};

#endif