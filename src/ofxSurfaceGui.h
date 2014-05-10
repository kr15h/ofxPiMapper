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
    
    enum editMode {
        NONE,
        TEXTURE_MAPPING,
        PROJECTION_MAPPING
    };
    
    void setup(ofxTriangleSurface& surfaceForGui);
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void setMode(editMode newMode);
    
    editMode getMode();
    
private:
    editMode mode;
    ofxTriangleSurface* surface;
    
    vector<ofxCircleJoint> projectionMappingJoints;
    vector<ofxCircleJoint> textureMappingJoints;
    
    void addProjectionMappingJoint();
    void addNumProjectionMappingJoints(int num);
    void addTextureMappingJoint();
    void addNumTextureMappingJoints(int num);
};

#endif