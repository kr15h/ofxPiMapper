#include "ofxSurfaceManagerGui.h"

ofxSurfaceManagerGui::ofxSurfaceManagerGui()
{
    surfaceManager = NULL;
    guiMode = ofxGuiMode::NONE;
    bDrag = false;
    registerMouseEvents();
    ofRegisterGetMessages(this);
}

ofxSurfaceManagerGui::~ofxSurfaceManagerGui()
{
    unregisterMouseEvents();
    ofUnregisterGetMessages(this);
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
        
        // highlight selected surface
        drawSelectedSurfaceHighlight();
        
        // hilight selected surface texture
        drawSelectedSurfaceTextureHighlight();
        
        // draw texture editing GUI on top
        textureEditor.draw();
        
    } else if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
        
        // draw projection surfaces first
        surfaceManager->draw();
        
        // highlight selected surface
        drawSelectedSurfaceHighlight();
        
        // draw projection mapping editing gui
        projectionEditor.draw();
        
    } else if ( guiMode == ofxGuiMode::SOURCE_SELECTION ) {
        // draw projection surfaces first
        surfaceManager->draw();
        
        // highlight selected surface
        drawSelectedSurfaceHighlight();
        
        sourcesEditor.draw();
    }
}

void ofxSurfaceManagerGui::mousePressed(ofMouseEventArgs &args)
{
    if ( guiMode == ofxGuiMode::NONE ) {
        return;
    } else if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
        
        bool bSurfaceSelected = false;
        
        ofxCircleJoint* hitJoint = textureEditor.hitTestJoints(ofVec2f(args.x, args.y));
        if ( hitJoint != NULL ) {
            hitJoint->startDrag();
            bSurfaceSelected = true;
        }
        
        if ( surfaceManager->getSelectedSurface() != NULL && !bSurfaceSelected ) {
            // hittest texture area to see if we are hitting the texture surface
            if ( surfaceManager->getSelectedSurface()->getTextureHitArea().inside(args.x, args.y) ) {
                clickPosition = ofVec2f(args.x, args.y);
                startDrag();
            }
        }
        
    } else if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
        
        bool bSurfaceSelected = false;
        
        ofxCircleJoint* hitJoint = projectionEditor.hitTestJoints(ofVec2f(args.x, args.y));
        if ( hitJoint != NULL ) {
            hitJoint->startDrag();
            bSurfaceSelected = true;
        }
        
        // attempt to select surface, loop from end to beginning
        if ( !bSurfaceSelected ){
            for ( int i=surfaceManager->size()-1; i>=0; i-- ) {
                if ( surfaceManager->getSurface(i)->hitTest( ofVec2f(args.x, args.y) ) ) {
                    projectionEditor.clearJoints();
                    surfaceManager->selectSurface(i);
                    projectionEditor.createJoints();
                    bSurfaceSelected = true;
                    break;
                }
            }
        }
        
        if ( bSurfaceSelected && hitJoint == NULL ) {
            // if not hitting the joints, start drag only if we have a selected surface
            clickPosition = ofVec2f(args.x, args.y);
            startDrag();
        }
        
        if ( !bSurfaceSelected ) {
            // unselect if no surface selected
            projectionEditor.clearJoints();
            surfaceManager->deselectSurface();
        }
    } else if ( guiMode == ofxGuiMode::SOURCE_SELECTION ) {
        
    }
}

void ofxSurfaceManagerGui::mouseReleased(ofMouseEventArgs &args)
{
    stopDrag();
    projectionEditor.stopDragJoints();
    textureEditor.stopDragJoints();
}

void ofxSurfaceManagerGui::mouseDragged(ofMouseEventArgs &args)
{
    if (bDrag) {
        ofVec2f mousePosition = ofVec2f(args.x, args.y);
        ofVec2f distance = mousePosition - clickPosition;
        
        if ( guiMode == ofxGuiMode::PROJECTION_MAPPING ) {
            // add this distance to all vertices in surface
            projectionEditor.moveSelectedSurface(distance);
        } else if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
            textureEditor.moveTexCoords(distance);
        }
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
        newGuiMode != ofxGuiMode::PROJECTION_MAPPING &&
        newGuiMode != ofxGuiMode::SOURCE_SELECTION) {
        throw std::runtime_error("Trying to set invalid mode.");
    }
    
    guiMode = newGuiMode;
    
    if ( guiMode == ofxGuiMode::SOURCE_SELECTION ) {
        sourcesEditor.enable();
    } else {
        sourcesEditor.disable();
    }
    
    if ( guiMode == ofxGuiMode::TEXTURE_MAPPING ) {
        // refresh texture editor surface reference
        textureEditor.setSurface(surfaceManager->getSelectedSurface());
    }
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

void ofxSurfaceManagerGui::drawSelectedSurfaceTextureHighlight()
{
    if ( surfaceManager->getSelectedSurface() == NULL ) return;
    
    ofPolyline line = surfaceManager->getSelectedSurface()->getTextureHitArea();
    
    ofPushStyle();
    ofSetLineWidth(1);
    ofSetColor(255, 255, 0, 255);
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

void ofxSurfaceManagerGui::gotMessage(ofMessage& msg)
{
    cout << msg.message << endl;
    
    if ( msg.message == "imageLoaded" ) {
        // assign texture to selected source
        if (surfaceManager->getSelectedSurface() == NULL){
            return;
        }
        surfaceManager->getSelectedSurface()->setTexture( sourcesEditor.getTexture(sourcesEditor.getLoadedTexCount()-1) );
    }
}