#ifndef H_OFX_SURFACE_GUI
#define H_OFX_SURFACE_GUI

#include "ofMain.h"
#include "ofxTriangleSurface.h"
#include "ofxCircleJoint.h"

class ofxSurfaceGui
{
public:
    ofxSurfaceGui();
    ~ofxSurfaceGui();
    
    void setup(ofxTriangleSurface& surfaceForGui);
    
private:
    ofxTriangleSurface* surface;
    ofxCircleJoint joints[100];
    int jointCounter;
    
    void addJoint();
    void addNumJoints(int num);
};

#endif