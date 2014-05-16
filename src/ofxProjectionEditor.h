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
    void registerKeyEvents();
    void unregisterKeyEvents();
    
    void enable();
    void disable();
    
    void update(ofEventArgs& args);
    void draw();
    void mouseDragged(ofMouseEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    void gotMessage(ofMessage& msg);
    void setSurfaceManager(ofxSurfaceManager* newSurfaceManager);
    void clearJoints();
    void createJoints();
    void updateJoints();
    void unselectAllJoints();
    void moveSelectedSurface(ofVec2f by);
    void stopDragJoints();
    void updateVertices();
    void moveSelection(ofVec2f by);
    ofxCircleJoint* hitTestJoints(ofVec2f pos);
    
private:
    ofxSurfaceManager* surfaceManager;
    vector<ofxCircleJoint*> joints;
    bool bShiftKeyDown;
    
    void drawJoints();
};

#endif