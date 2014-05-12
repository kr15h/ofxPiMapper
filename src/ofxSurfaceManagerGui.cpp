#include "ofxSurfaceManagerGui.h"

ofxSurfaceManagerGui::ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
}

ofxSurfaceManagerGui::ofxSurfaceManagerGui(ofxSurfaceManager* newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
}

ofxSurfaceManagerGui::~ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
}