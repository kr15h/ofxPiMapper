#include "ofxSurfaceManagerGui.h"

ofxSurfaceManagerGui::ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
    guiMode = ofxGuiMode::NONE;
    bDrag = false;
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
    ofAddListener(ofEvents().mouseReleased, this, &ofxSurfaceManagerGui::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this, &ofxSurfaceManagerGui::mouseDragged);
}

void ofxSurfaceManagerGui::unregisterMouseEvents()
{
    ofRemoveListener(ofEvents().mousePressed, this, &ofxSurfaceManagerGui::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxSurfaceManagerGui::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxSurfaceManagerGui::mouseDragged);
}

void ofxSurfaceManagerGui::draw()
{
    if ( surfaceManager == NULL ) return;
    
    if ( guiMode == ofxGuiMode::NONE ) {
        surfaceManager->draw();
    } else if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
        
        // draw the texture of the selected surface
        if ( surfaceManager->getSelectedSurface() != NULL ) {
            surfaceManager->getSelectedSurface()->drawTexture( ofVec2f(0,0) );
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
        return;
    } else if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
        // attempt to select surface, loop from end to beginning
        bool bSurfaceSelected = false;
        for ( int i=surfaceManager->size()-1; i>=0; i-- ) {
            if ( surfaceManager->getSurface(i)->hitTest( ofVec2f(args.x, args.y) ) ) {
                projectionEditor.clearJoints();
                surfaceManager->selectSurface(i);
                projectionEditor.createJoints();
                bSurfaceSelected = true;
                break;
            }
        }
        
        // Check if hitting one of the joints as that also counts as hit when surface is selected
        if ( projectionEditor.hitTestJoints(ofVec2f(args.x, args.y)) ) {
            bSurfaceSelected = true;
        } else if ( bSurfaceSelected ) {
            // if not hitting the joints, start drag only if we have a selected surface
            clickPosition = ofVec2f(args.x, args.y);
            startDrag();
        }
        
        if ( !bSurfaceSelected ) {
            // unselect if no surface selected
            projectionEditor.clearJoints();
            surfaceManager->deselectSurface();
        }
    }
}

void ofxSurfaceManagerGui::mouseReleased(ofMouseEventArgs &args)
{
    stopDrag();
}

void ofxSurfaceManagerGui::mouseDragged(ofMouseEventArgs &args)
{
    if (bDrag) {
        ofVec2f mousePosition = ofVec2f(args.x, args.y);
        ofVec2f distance = mousePosition - clickPosition;
        // add this distance to all vertices in surface
        projectionEditor.moveSelectedSurface(distance);
        clickPosition = mousePosition;
    }
}

void ofxSurfaceManagerGui::setSurfaceManager(ofxSurfaceManager* newSurfaceManager)
{
    surfaceManager = newSurfaceManager;
    projectionEditor.setSurfaceManager( surfaceManager );
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

void ofxSurfaceManagerGui::drawSelectedSurfaceHighlight()
{
    if ( surfaceManager->getSelectedSurface() == NULL ) return;
    
    ofPolyline line = surfaceManager->getSelectedSurface()->getHitArea();
    
    ofPushStyle();
    ofSetLineWidth(1);
    ofSetColor(255, 255, 255, 255);
    line.draw();
    ofPopStyle();
}

void ofxSurfaceManagerGui::startDrag()
{
    bDrag = true;
}

void ofxSurfaceManagerGui::stopDrag()
{
    bDrag = false;
}