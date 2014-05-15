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

void ofxSurfaceManager::saveXmlSettings(string fileName)
{
    xmlSettings.clear();
    
    // save surfaces
    xmlSettings.addTag("surfaces");
    xmlSettings.pushTag("surfaces");
    for ( int i=0; i<surfaces.size(); i++ ) {
        
        xmlSettings.addTag("surface");
        xmlSettings.pushTag("surface", i);
        ofxBaseSurface* surface = surfaces[i];
        
        xmlSettings.addTag("vertices");
        xmlSettings.pushTag("vertices");
        vector<ofVec3f>* vertices = &surface->getVertices();
        for ( int j=0; j<vertices->size(); j++ ) {
            xmlSettings.addTag("vertex");
            xmlSettings.pushTag("vertex", j);
            ofVec3f* vertex = &(*vertices)[j];
            xmlSettings.addValue("x", vertex->x);
            xmlSettings.addValue("y", vertex->y);
            
            // we don't need z as it will be 0 anyways
            
            xmlSettings.popTag(); // vertex
        }
        xmlSettings.popTag(); // vertices
        
        xmlSettings.addTag("texCoords");
        xmlSettings.pushTag("texCoords");
        vector<ofVec2f>* texCoords = &surface->getTexCoords();
        for ( int j=0; j<texCoords->size(); j++ ) {
            xmlSettings.addTag("texCoord");
            xmlSettings.pushTag("texCoord", j);
            ofVec2f* texCoord = &(*texCoords)[j];
            xmlSettings.addValue("x", texCoord->x);
            xmlSettings.addValue("y", texCoord->y);
            xmlSettings.popTag(); // texCoord
        }
        xmlSettings.popTag(); // texCoords
        
        xmlSettings.addTag("source");
        xmlSettings.pushTag("source");
        
        xmlSettings.addValue("source-type", "image");
        xmlSettings.addValue("source-name", getSurfaceSourceName(surface));
        //xmlSettings.addValue("source-path", "/root/etc/image.jpg");
        
        xmlSettings.popTag(); // source
        
        xmlSettings.popTag(); // surface
    }
    xmlSettings.popTag(); // surfaces
    
    xmlSettings.save(fileName);
}

void ofxSurfaceManager::loadXmlSettings(string fileName)
{
    
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
    
    return getSurfaceSourceName( selectedSurface );
}

string ofxSurfaceManager::getSurfaceSourceName(ofxBaseSurface *surface)
{
    ofTexture* tex = surface->getTexture();
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



