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
    ofxBaseSurface* selectSurface(int index);
    void deselectSurface();
    void drawSelectedSurfaceHighlight();
    
private:
    ofxSurfaceManager* surfaceManager;
    ofxTextureEditor textureEditor;
    ofxProjectionEditor projectionEditor;
    int guiMode;
    ofxBaseSurface* selectedSurface;
};

#endif