#ifndef H_OFX_TEXTURE_EDITOR
#define H_OFX_TEXTURE_EDITOR

#include "ofxBaseSurface.h"
#include "ofxCircleJoint.h"

class ofxTextureEditor
{
public:
    ofxTextureEditor();
    ~ofxTextureEditor();
    
    void draw();
    void drawJoints();
    void setSurface(ofxBaseSurface* newSurface);
    void clear();
    void createJoints();
    void clearJoints();
    void moveTexCoords(ofVec2f by);
    
private:
    ofxBaseSurface* surface;
    vector<ofxBaseJoint*> joints;
    
};

#endif