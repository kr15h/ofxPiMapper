#ifndef H_OFX_PROJECTION_EDITOR
#define H_OFX_PROJECTION_EDITOR

#include "ofxSurfaceManager.h"
#include "ofxCircleJoint.h"

class ofxProjectionEditor
{
public:
    ofxProjectionEditor();
    ~ofxProjectionEditor();
    
    void registerAppEvents();
    void unregisterAppEvents();
    void registerMouseEvents();
    void unregisterMouseEvents();
    
    void update(ofEventArgs& args);
    void draw();
    void mouseDragged(ofMouseEventArgs& args);
    void gotMessage(ofMessage& msg);
    void setSurfaceManager(ofxSurfaceManager* newSurfaceManager);
    void clearJoints();
    void createJoints();
    void updateJoints();
    void moveSelectedSurface(ofVec2f by);
    void stopDragJoints();
    void updateVertices();
    ofxCircleJoint* hitTestJoints(ofVec2f pos);
    
private:
    ofxSurfaceManager* surfaceManager;
    vector<ofxCircleJoint*> joints;
    
    void drawJoints();
};

#endif