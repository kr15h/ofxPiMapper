#ifndef H_OFX_SURFACE_MANAGER_GUI
#define H_OFX_SURFACE_MANAGER_GUI

#include "ofEvents.h"
#include "ofxSurfaceManager.h"
#include "ofxTextureEditor.h"
#include "ofxProjectionEditor.h"
#include "ofxGuiMode.h"

class ofxSurfaceManagerGui
{
public:
    ofxSurfaceManagerGui();
    ~ofxSurfaceManagerGui();
    
    void registerMouseEvents();
    void unregisterMouseEvents();
    
    void draw();
    void mousePressed(ofMouseEventArgs& args);
    void setSurfaceManager(ofxSurfaceManager* newSurfaceManager);
    void setMode(int newGuiMode);
    void drawSelectedSurfaceHighlight();
    
private:
    ofxSurfaceManager* surfaceManager;
    ofxTextureEditor textureEditor;
    ofxProjectionEditor projectionEditor;
    int guiMode;
};

#endif