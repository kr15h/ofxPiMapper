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

void ofxSurfaceManagerGui::draw()
{
    if ( surfaceManager == NULL ) return;
    
    if ( guiMode == ofxGuiMode::NONE ) {
        // Do nothing
    } else if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
        // Draw texture mapping GUI
    } else if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
        // Draw projection mapping GUI
    }
}

void ofxSurfaceManagerGui::setSurfaceManager(ofxSurfaceManager* newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
}