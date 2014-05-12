#include "ofxSurfaceManagerGui.h"

ofxSurfaceManagerGui::ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
    guiMode = ofxGuiMode::NONE;
    selectedSurface = NULL;
    registerMouseEvents();
}

ofxSurfaceManagerGui::~ofxSurfaceManagerGui()
{
    unregisterMouseEvents();
    surfaceManager = NULL;
}

void ofxSurfaceManagerGui::registerMouseEvents()
{
    ofAddListener(ofEvents().mousePressed, this, &ofxSurfaceManagerGui::mousePressed);
}

void ofxSurfaceManagerGui::unregisterMouseEvents()
{
    ofRemoveListener(ofEvents().mousePressed, this, &ofxSurfaceManagerGui::mousePressed);
}

void ofxSurfaceManagerGui::draw()
{
    if ( surfaceManager == NULL ) return;
    
    if ( guiMode == ofxGuiMode::NONE ) {
        surfaceManager->draw();
    } else if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
        
        // draw the texture of the selected surface
        if ( selectedSurface != NULL ) {
            selectedSurface->drawTexture( ofVec2f(0,0) );
        }
        
        // draw surfaces with opacity
        ofPushStyle();
        ofSetColor(255, 255, 255, 200);
        surfaceManager->draw();
        ofPopStyle();
        
        // hilight selected surface
        drawSelectedSurfaceHighlight();
        
        // draw texture editing GUI on top
        textureEditor.draw();
        
    } else if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
        
        // draw projection surfaces first
        surfaceManager->draw();
        
        // highlight selected surface
        drawSelectedSurfaceHighlight();
        
        // draw projection mapping editing gui
        projectionEditor.draw();
        
    }
}

void ofxSurfaceManagerGui::mousePressed(ofMouseEventArgs &args)
{
    if ( guiMode == ofxGuiMode::NONE ) {
        return;
    } else if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
        
    } else if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
        // attempt to select surface, loop from end to beginning
        for ( int i=surfaceManager->size()-1; i>=0; i-- ) {
            if ( surfaceManager->getSurface(i)->hitTest( ofVec2f(args.x, args.y) ) ) {
                selectSurface(i);
                break;
            }
        }
    }
}

void ofxSurfaceManagerGui::setSurfaceManager(ofxSurfaceManager* newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
}

void ofxSurfaceManagerGui::setMode(int newGuiMode)
{
    if (newGuiMode != ofxGuiMode::NONE &&
        newGuiMode != ofxGuiMode::TEXTURE_MAPPING &&
        newGuiMode != ofxGuiMode::PROJECTION_MAPPING) {
        throw std::runtime_error("Trying to set invalid mode.");
    }
    
    guiMode = newGuiMode;
}

ofxBaseSurface* ofxSurfaceManagerGui::selectSurface(int index)
{
    if ( index >= surfaceManager->size() ) {
        throw std::runtime_error("Surface index out of bounds.");
    }
    
    selectedSurface = surfaceManager->getSurface(index);
}

void ofxSurfaceManagerGui::deselectSurface()
{
    selectedSurface = NULL;
}

void ofxSurfaceManagerGui::drawSelectedSurfaceHighlight()
{
    if ( selectedSurface == NULL ) return;
    
    ofPolyline line = selectedSurface->getHitArea();
    
    ofPushStyle();
    ofSetLineWidth(1);
    ofSetColor(255, 255, 255, 255);
    line.draw();
    ofPopStyle();
}