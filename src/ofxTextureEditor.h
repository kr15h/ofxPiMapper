#ifndef H_OFX_TEXTURE_EDITOR
#define H_OFX_TEXTURE_EDITOR

#include "ofxBaseSurface.h"

class ofxTextureEditor
{
public:
    ofxTextureEditor();
    ofxTextureEditor(ofxBaseSurface* newSurface);
    ~ofxTextureEditor();
    
    void draw();
    void setSurface(ofxBaseSurface* newSurface);
    void clear();
    
private:
    ofxBaseSurface* surface;
    
};

#endif