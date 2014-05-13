#include "ofxSurfaceManager.h"

ofxSurfaceManager::ofxSurfaceManager()
{
    
}

ofxSurfaceManager::~ofxSurfaceManager()
{
    clear();
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

void ofxSurfaceManager::manageMemory()
{
    // check if each of the sources is assigned to a surface or not
    for ( int i=0; i<loadedImageSources.size(); i++ ) {
        bool bAssigned = false;
        
        for ( int j=0; j<surfaces.size(); j++ ) {
            if ( surfaces[j]->getTexture() == &loadedImageSources[i]->getTextureReference() ) {
                bAssigned = true;
                break;
            }
        }
        
        if ( !bAssigned ) {
            // purge the image source from memory
            delete loadedImageSources[i];
            loadedImageSources.erase(loadedImageSources.begin()+i);
            cout << "Deleting image source: " << loadedImageSourceNames[i] << endl;
            loadedImageSourceNames.erase(loadedImageSourceNames.begin()+i);
            i--;
        }
    }
}

void ofxSurfaceManager::clear()
{
    // delete all extra allocations from the heap
    while ( surfaces.size() ) {
        delete surfaces.back();
        surfaces.pop_back();
    }
    
    while ( loadedImageSources.size() ) {
        delete loadedImageSources.back();
        loadedImageSources.pop_back();
    }
    
    while ( loadedImageSourceNames.size() ) {
        loadedImageSourceNames.pop_back();
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

ofTexture* ofxSurfaceManager::loadImageSource(string name, string path)
{
    // check if it is loaded
    for ( int i=0; i<loadedImageSourceNames.size(); i++ ) {
        if ( loadedImageSourceNames[i] == name ) {
            // this image is already loaded
            return &loadedImageSources[i]->getTextureReference();
        }
    }
    
    // not loaded - load
    ofImage* image = new ofImage();
    image->loadImage(path);
    loadedImageSources.push_back(image);
    loadedImageSourceNames.push_back(name);
    return &image->getTextureReference();
}

string ofxSurfaceManager::getSelectedSurfaceSourceName()
{
    if ( selectedSurface == NULL ) {
        return "none";
    }
    
    ofTexture* tex = selectedSurface->getTexture();
    for ( int i=0; i<loadedImageSources.size(); i++ ) {
        if (tex == &loadedImageSources[i]->getTextureReference()) {
            return loadedImageSourceNames[i];
        }
    }
    
    return "none";
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



