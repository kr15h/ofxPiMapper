#ifndef H_OFX_SURFACE_MANAGER
#define H_OFX_SURFACE_MANAGER

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
    ofxBaseSurface* selectSurface(int index);
    ofxBaseSurface* getSelectedSurface();
    void deselectSurface();
    
private:
    vector<ofxBaseSurface*> surfaces;
    ofxBaseSurface* selectedSurface;
};

#endif