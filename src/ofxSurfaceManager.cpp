#include "ofxSurfaceManager.h"

ofxSurfaceManager::ofxSurfaceManager()
{
    
}

ofxSurfaceManager::~ofxSurfaceManager()
{
    // delete all extra allocations from the heap
    while ( triangleSurfaces.size() ) {
        delete triangleSurfaces.back();
        triangleSurfaces.pop_back();
    }
    
    while ( surfaceGuis.size() ) {
        delete surfaceGuis.back();
        surfaceGuis.pop_back();
    }
}

void ofxSurfaceManager::setup()
{
    
}

void ofxSurfaceManager::update()
{
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        surfaceGuis[i]->update();
    }
}

void ofxSurfaceManager::draw()
{
    // Check GUI mode - we want to see the texture that we are editing
    // together with the actual surface being projection mapped.
    for ( int i=surfaceGuis.size()-1; i>=0; i-- ) {
        
        bool bDrawTexture = false;
        if ( surfaceGuis[i]->isSelected() && surfaceGuis[i]->getMode() == ofxSurfaceGui::TEXTURE_MAPPING ) {
            bDrawTexture = true;
        }
        
        if ( bDrawTexture ) {
            // Draw texture of the surface in the background
            //triangleSurface.getTexture()->draw(ofPoint(0,0));
            triangleSurfaces[i]->drawTexture(ofVec2f(0, 0));
            
            // Make the triangle surface transparent but still visible
            // while we map the texture coordinates.
            ofPushStyle();
            ofSetColor(255, 255, 255, 200);
        }
        
        triangleSurfaces[i]->draw();
        
        if ( bDrawTexture ) {
            ofPopStyle();
        }
        
        surfaceGuis[i]->draw();
    }
}

void ofxSurfaceManager::mousePressed(int x, int y, int button)
{
    bool bSurfaceSelected = false;
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        // check only if in projection mapping mode
        if ( surfaceGuis[i]->getMode() == ofxSurfaceGui::PROJECTION_MAPPING ) {
            if ( surfaceGuis[i]->hitTest(x, y) ) {
                unselectAllSurfaces();
                selectSurface(i);
                bSurfaceSelected = true;
                break; // we need to select just one surface
            }
        } else {
            bSurfaceSelected = true; // Hackish - we will need a lot of refractoring here later
        }
    }
    
    // execute mouse pressed events for surface GUIs
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        surfaceGuis[i]->mousePressed(x, y, button);
    }
    
    if (!bSurfaceSelected) {
        unselectAllSurfaces();
    }
}

void ofxSurfaceManager::mouseReleased(int x, int y, int button)
{
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        surfaceGuis[i]->mouseReleased(x, y, button);
    }
}

void ofxSurfaceManager::mouseDragged(int x, int y, int button)
{
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        surfaceGuis[i]->mouseDragged(x, y, button);
    }
}

void ofxSurfaceManager::addSurface()
{
    addTriangleSurface();
}

void ofxSurfaceManager::addSurface(ofTexture* texturePtr)
{
    addTriangleSurface(texturePtr);
}

void ofxSurfaceManager::addSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3)
{
    addTriangleSurface(v1, v2, v3, t1, t2, t3);
}

void ofxSurfaceManager::addSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3,
                                   ofVec2f t1, ofVec2f t2, ofVec2f t3,
                                   ofTexture *texturePtr)
{
    addTriangleSurface(v1, v2, v3, t1, t2, t3, texturePtr);
}

void ofxSurfaceManager::removeSurface(int index)
{
    if ( index >= surfaceGuis.size() ) {
        throw std::runtime_error("Surface index out of bounds.");
        return;
    }
    
    delete surfaceGuis[index];
    surfaceGuis.erase( surfaceGuis.begin()+index );
    delete triangleSurfaces[index];
    triangleSurfaces.erase( triangleSurfaces.begin()+index );
}

void ofxSurfaceManager::setGuiMode(ofxSurfaceGui::editMode editMode)
{
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        surfaceGuis[i]->setMode(editMode);
    }
}

void ofxSurfaceManager::selectSurface(int index)
{
    if ( index >= surfaceGuis.size() ){
        throw std::runtime_error("Surface index out of bounds.");
        return;
    }
    surfaceGuis[index]->select();
}

void ofxSurfaceManager::unselectAllSurfaces()
{
    for ( int i=0; i<surfaceGuis.size(); i++ ) {
        surfaceGuis[i]->unselect();
    }
}

int ofxSurfaceManager::size()
{
    return surfaceGuis.size();
}

void ofxSurfaceManager::addTriangleSurface()
{
    triangleSurfaces.push_back( new ofxTriangleSurface() );
    surfaceGuis.push_back( new ofxSurfaceGui() );
    surfaceGuis.back()->setup( *triangleSurfaces.back() );
}

void ofxSurfaceManager::addTriangleSurface(ofTexture* texturePtr)
{
    addTriangleSurface();
    triangleSurfaces.back()->setTexture(texturePtr);
}

void ofxSurfaceManager::addTriangleSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3)
{
    addTriangleSurface();
    triangleSurfaces.back()->setup(v1, v2, v3, t1, t2, t3, triangleSurfaces.back()->getTexture());
    surfaceGuis.back()->updateJoints();
}

void ofxSurfaceManager::addTriangleSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3, ofTexture* texturePtr)
{
    addTriangleSurface();
    triangleSurfaces.back()->setup(v1, v2, v3, t1, t2, t3, texturePtr);
    surfaceGuis.back()->updateJoints();
}