#include "ofxSurfaceManager.h"

ofxSurfaceManager::ofxSurfaceManager()
{
    
}

ofxSurfaceManager::~ofxSurfaceManager()
{
    // delete all extra allocations from the heap
    while ( surfaces.size() ) {
        delete surfaces.back();
        surfaces.pop_back();
    }
}

void ofxSurfaceManager::draw()
{
    for ( int i=0; i<surfaces.size(); i++ ) {
        surfaces[i]->draw();
    }
}

void ofxSurfaceManager::addSurface(int surfaceType)
{
    if ( surfaceType == ofxSurfaceType::TRIANGLE_SURFACE ) {
        surfaces.push_back( new ofxTriangleSurface() );
    } else {
        throw std::runtime_error("Attempt to add non-existing surface type.");
    }
}

ofxBaseSurface* ofxSurfaceManager::selectSurface(int index)
{
    if ( index >= surfaces.size() ) {
        throw std::runtime_error("Surface index out of bounds.");
    }
    
    selectedSurface = surfaces[index];
}

ofxBaseSurface* ofxSurfaceManager::getSelectedSurface()
{    
    return selectedSurface;
}

void ofxSurfaceManager::deselectSurface()
{
    selectedSurface = NULL;
}

ofxBaseSurface* ofxSurfaceManager::getSurface(int index)
{
    if ( index >= surfaces.size() ) {
        throw std::runtime_error("Surface index out of bounds.");
        return NULL;
    }
    
    return surfaces[index];
}

int ofxSurfaceManager::size()
{
    return surfaces.size();
}

