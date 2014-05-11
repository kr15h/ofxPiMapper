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
    void select();
    void unselect();
    bool hitTest(float x, float y);
    bool isSelected();
    
    editMode getMode();
    
private:
    editMode mode;
    ofxTriangleSurface* surface;
    ofPolyline textureHitarea;
    ofPolyline projectionHitarea;
    ofVec2f clickPosition;
    
    vector<ofxCircleJoint> projectionMappingJoints;
    vector<ofxCircleJoint> textureMappingJoints;
    
    bool bTextureMappingJointSelected;
    bool bProjectionMappingJointSelected;
    bool bTextureDragging;
    bool bProjectionDragging;
    bool bSelected;
    
    bool isProjectionMappingJointSelected();
    bool isTextureMappingJointSelected();
    bool projectionAreaExists();
    
    void addProjectionMappingJoint();
    void addNumProjectionMappingJoints(int num);
    void addTextureMappingJoint();
    void addNumTextureMappingJoints(int num);
    void updateTextureHitarea();
    void updateProjectionHitarea();
    void dragTextureArea();
    void dragProjectionArea();
    void stopDrag();
};

#endif