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
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    
private:
    ofxTriangleSurface* surface;
    vector<ofxCircleJoint> joints;
    
    void addJoint();
    void addNumJoints(int num);
};

#endif