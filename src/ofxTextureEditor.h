#ifndef H_OFX_TEXTURE_EDITOR
#define H_OFX_TEXTURE_EDITOR

#include "ofEvents.h"
#include "ofxBaseSurface.h"
#include "ofxCircleJoint.h"

class ofxTextureEditor
{
public:
    ofxTextureEditor();
    ~ofxTextureEditor();
    
    void registerAppEvents();
    void unregisterAppEvents();
    void registerKeyEvents();
    void unregisterKeyEvents();
    void enable();
    void disable();
    
    void update(ofEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
    void keyReleased(ofKeyEventArgs& args);
    void draw();
    void drawJoints();
    void setSurface(ofxBaseSurface* newSurface);
    void clear();
    void createJoints();
    void clearJoints();
    void unselectAllJoints();
    void moveTexCoords(ofVec2f by);
    void stopDragJoints();
    void moveSelection(ofVec2f by);
    ofxCircleJoint* hitTestJoints(ofVec2f pos);
    
private:
    ofxBaseSurface* surface;
    vector<ofxCircleJoint*> joints;
    bool bShiftKeyDown;
};

#endif