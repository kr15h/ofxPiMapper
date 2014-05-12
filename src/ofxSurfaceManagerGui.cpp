#include "ofxSurfaceManagerGui.h"

ofxSurfaceManagerGui::ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
    guiMode = ofxGuiMode::NONE;
}

ofxSurfaceManagerGui::ofxSurfaceManagerGui(ofxSurfaceManager* newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
}

ofxSurfaceManagerGui::~ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
}