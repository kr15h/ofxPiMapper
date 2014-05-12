#ifndef H_OFX_PROJECTION_EDITOR
#define H_OFX_PROJECTION_EDITOR

#include "ofxSurfaceManager.h"
#include "ofxCircleJoint.h"

class ofxProjectionEditor
{
public:
    ofxProjectionEditor();
    ~ofxProjectionEditor();
    
    void draw();
    void setSurfaceManager(ofxSurfaceManager* newSurfaceManager);
    void clearJoints();
    void createJoints();
    void updateJoints();
    void moveSelectedSurface(ofVec2f by);
    bool hitTestJoints(ofVec2f pos);
    
private:
    ofxSurfaceManager* surfaceManager;
    vector<ofxCircleJoint*> joints;
    
    void drawJoints();
};

#endif