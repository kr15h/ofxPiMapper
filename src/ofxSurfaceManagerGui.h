#ifndef H_OFX_SURFACE_MANAGER_GUI
#define H_OFX_SURFACE_MANAGER_GUI

#include "ofMain.h"
#include "ofxSurfaceManager.h"
#include "ofxTextureEditor.h"
#include "ofxProjectionEditor.h"
#include "ofxGuiMode.h"

class ofxSurfaceManagerGui
{
public:
    ofxSurfaceManagerGui();
    ofxSurfaceManagerGui(ofxSurfaceManager* newSurfaceManager);
    ~ofxSurfaceManagerGui();
    
    void draw();
    
    void setSurfaceManager(ofxSurfaceManager* newSurfaceManager);
    
private:
    ofxSurfaceManager* surfaceManager;
    ofxTextureEditor textureEditor;
    ofxProjectionEditor projectionEditor;
    int guiMode;
};

#endif