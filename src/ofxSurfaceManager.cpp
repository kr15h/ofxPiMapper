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

void ofxSurfaceManager::addSurface(int surfaceType, ofTexture* texturePtr)
{
    if ( surfaceType == ofxSurfaceType::TRIANGLE_SURFACE ) {
        surfaces.push_back( new ofxTriangleSurface() );
        surfaces.back()->setTexture(texturePtr);
    } else {
        throw std::runtime_error("Attempt to add non-existing surface type.");
    }
}

void ofxSurfaceManager::addSurface(int surfaceType, vector<ofVec2f> vertices, vector<ofVec2f> texCoords)
{
    if ( surfaceType == ofxSurfaceType::TRIANGLE_SURFACE ) {
        
        if ( vertices.size() < 3 ) {
            throw std::runtime_error("There must be 3 vertices for a triangle surface.");
        } else if (texCoords.size() < 3) {
            throw std::runtime_error("Thre must be 3 texture coordinates for a triangle surface.");
        }
        
        surfaces.push_back( new ofxTriangleSurface() );
        
        for ( int i=0; i<3; i++ ) {
            surfaces.back()->setVertex(i, vertices[i]);
            surfaces.back()->setTexCoord(i, texCoords[i]);
        }
        
    } else {
        throw std::runtime_error("Attempt to add non-existing surface type.");
    }

}

void ofxSurfaceManager::addSurface(int surfaceType, ofTexture* texturePtr, vector<ofVec2f> vertices, vector<ofVec2f> texCoords)
{
    if ( surfaceType == ofxSurfaceType::TRIANGLE_SURFACE ) {
        
        if ( vertices.size() < 3 ) {
            throw std::runtime_error("There must be 3 vertices for a triangle surface.");
        } else if (texCoords.size() < 3) {
            throw std::runtime_error("Thre must be 3 texture coordinates for a triangle surface.");
        }
        
        surfaces.push_back( new ofxTriangleSurface() );
        surfaces.back()->setTexture(texturePtr);
        
        for ( int i=0; i<3; i++ ) {
            surfaces.back()->setVertex(i, vertices[i]);
            surfaces.back()->setTexCoord(i, texCoords[i]);
        }
        
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

