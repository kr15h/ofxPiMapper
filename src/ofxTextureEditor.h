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
    
    void update(ofEventArgs& args);
    void draw();
    void drawJoints();
    void setSurface(ofxBaseSurface* newSurface);
    void clear();
    void createJoints();
    void clearJoints();
    void moveTexCoords(ofVec2f by);
    void stopDragJoints();
    ofxCircleJoint* hitTestJoints(ofVec2f pos);
    
private:
    ofxBaseSurface* surface;
    vector<ofxCircleJoint*> joints;
    
};

#endif