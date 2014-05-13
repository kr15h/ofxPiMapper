#ifndef H_OFX_SURFACE_MANAGER
#define H_OFX_SURFACE_MANAGER

#include "ofxBaseSurface.h"
#include "ofxTriangleSurface.h"
#include "ofxSurfaceType.h"
#include "ofEvents.h"

using namespace std;

class ofxSurfaceManager
{
public:
    ofxSurfaceManager();
    ~ofxSurfaceManager();
    
    void draw();
    void addSurface(int surfaceType);
    void addSurface(int surfaceType, ofTexture* texturePtr);
    void addSurface(int surfaceType, vector<ofVec2f> vertices, vector<ofVec2f> texCoords);
    void addSurface(int surfaceType, ofTexture* texturePtr, vector<ofVec2f> vertices, vector<ofVec2f> texCoords);
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