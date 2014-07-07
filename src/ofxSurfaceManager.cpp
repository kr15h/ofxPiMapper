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
    } 
    else if (surfaceType == ofxSurfaceType::QUAD_SURFACE ) {
        surfaces.push_back( new ofxQuadSurface() );
    }
    else {
        throw std::runtime_error("Attempt to add non-existing surface type.");
    }
}

void ofxSurfaceManager::addSurface(int surfaceType, ofTexture* texturePtr)
{
    if ( surfaceType == ofxSurfaceType::TRIANGLE_SURFACE ) {
        surfaces.push_back( new ofxTriangleSurface() );
        surfaces.back()->setTexture(texturePtr);
    } 
    else if (surfaceType == ofxSurfaceType::QUAD_SURFACE ) {
        surfaces.push_back( new ofxQuadSurface() );
        surfaces.back()->setTexture(texturePtr);
    }
    else {
        throw std::runtime_error("Attempt to add non-existing surface type.");
    }
}

void ofxSurfaceManager::addSurface(int surfaceType, vector<ofVec2f> vertices, vector<ofVec2f> texCoords)
{
    if ( surfaceType == ofxSurfaceType::TRIANGLE_SURFACE ) {
        
        if ( vertices.size() < 3 ) {
            throw std::runtime_error("There must be 3 vertices for a triangle surface.");
        } else if (texCoords.size() < 3) {
            throw std::runtime_error("There must be 3 texture coordinates for a triangle surface.");
        }
        
        surfaces.push_back( new ofxTriangleSurface() );
        
        for ( int i=0; i<3; i++ ) {
            surfaces.back()->setVertex(i, vertices[i]);
            surfaces.back()->setTexCoord(i, texCoords[i]);
        }
        
    } 
    else if (surfaceType == ofxSurfaceType::QUAD_SURFACE ) {
        if ( vertices.size() < 4 ) {
            throw std::runtime_error("There must be 4 vertices for a quad surface.");
        } else if (texCoords.size() < 4) {
            throw std::runtime_error("There must be 4 texture coordinates for a quad surface.");
        }
        
        surfaces.push_back( new ofxQuadSurface() );
        
        for ( int i=0; i<4; i++ ) {
            surfaces.back()->setVertex(i, vertices[i]);
            surfaces.back()->setTexCoord(i, texCoords[i]);
        }
    }
    else {
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
        
    } 
    else if (surfaceType == ofxSurfaceType::QUAD_SURFACE ) {
        if ( vertices.size() < 4 ) {
            throw std::runtime_error("There must be 4 vertices for a quad surface.");
        } else if (texCoords.size() < 4) {
            throw std::runtime_error("Thre must be 4 texture coordinates for a quad surface.");
        }
        
        surfaces.push_back( new ofxQuadSurface() );
        surfaces.back()->setTexture(texturePtr);
        
        for ( int i=0; i<4; i++ ) {
            surfaces.back()->setVertex(i, vertices[i]);
            surfaces.back()->setTexCoord(i, texCoords[i]);
        }
    }
    else {
        throw std::runtime_error("Attempt to add non-existing surface type.");
    }
}

void ofxSurfaceManager::removeSelectedSurface()
{
    if ( selectedSurface == NULL ) return;
    
    for ( int i=0; i<surfaces.size(); i++ ) {
        if ( surfaces[i] == selectedSurface ) {
            delete surfaces[i];
            surfaces.erase(surfaces.begin()+i);
            selectedSurface = NULL;
            break;
        }
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

// String getTypeString(ofxSurfaceType e)
// {
//   switch e
//   {
//       case TRINAGLE_SURFACE: return "TRINAGLE_SURFACE";
//       case QUAD_SURFACE: return "QUAD_SURFACE";
//       default: throw Exception("Bad MyEnum");
//   }
// }

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


        // xmlSettings.addTag("type");
        // xmlSettings.pushTag("type");
        // // surfaceType == ofxSurfaceType::TRIANGLE_SURFACE
        // ofxSurfaceType surfaceType = &surface->getType();
        // xmlSettings.addValue("surface-type", surfaceType);
        // xmlSettings.popTag(); // type

        xmlSettings.popTag(); // surface
    }
    xmlSettings.popTag(); // surfaces
    
    xmlSettings.save(fileName);
}

void ofxSurfaceManager::loadXmlSettings(string fileName)
{
    ofLog(OF_LOG_WARNING, "A load XML settings...");

    if (!xmlSettings.loadFile(fileName)){
        ofLog(OF_LOG_WARNING, "Could not load XML settings.");
        return;
    }
    
    if (!xmlSettings.tagExists("surfaces")){
        ofLog(OF_LOG_WARNING, "XML settings is empty or has wrong markup.");
        return;
    }
    
    xmlSettings.pushTag("surfaces");
    
    int numSurfaces = xmlSettings.getNumTags("surface");
    for ( int i=0; i<numSurfaces; i++ ) {
        xmlSettings.pushTag("surface", i);
        
        // attempt to load surface source
        xmlSettings.pushTag("source");
        string sourceType = xmlSettings.getValue("source-type", "image");
        string sourceName = xmlSettings.getValue("source-name", "none");
        ofTexture* sourceTexture = NULL;
        if ( sourceName != "none" ) {
            stringstream ss;
            ss << "sources/images/" << sourceName; // TODO: reuse constants here
            sourceTexture = loadImageSource(sourceName, ss.str());
        }
        xmlSettings.popTag(); // source

        // // attempt to load surface type
        // ofLog(OF_LOG_WARNING, "Attempt to load surface type.");
        // xmlSettings.pushTag("type");
        // string surfaceType = xmlSettings.getValue("surface-type", "TRIANGLE_SURFACE");
        // xmlSettings.popTag(); // type

        // get vertices (only for triangle surface for now)
        xmlSettings.pushTag("vertices");
        
        vector<ofVec2f> vertices;

        int vertexCount = vertices.size();
        // int vertexCount = vertices->size()

        //it's a triangle ?
        if (vertexCount == 3)
        // if (surfaceType == TRIANGLE_SURFACE)
        {
            xmlSettings.pushTag("vertex", 0);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("vertex", 1);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 100.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("vertex", 2);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 100.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.popTag(); // vertices
            
            xmlSettings.pushTag("texCoords");
            
            vector<ofVec2f> texCoords;
            
            xmlSettings.pushTag("texCoord", 0);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("texCoord", 1);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 1.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("texCoord", 2);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 1.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.popTag(); // texCoords
            
            
            // now we have variables sourceName and sourceTexture
            // by checking those we can use one or another addSurface method
            if ( sourceName != "none" && sourceTexture != NULL ) {
                addSurface(ofxSurfaceType::TRIANGLE_SURFACE, sourceTexture, vertices, texCoords);
            } else {
                addSurface(ofxSurfaceType::TRIANGLE_SURFACE, vertices, texCoords);
            }
            
            xmlSettings.popTag(); // surface
        }
        // it's a quad ?
        else if (vertexCount == 4)  
        // if (surface-type == QUAD_SURFACE)
        {
            ofSendMessage("create Quad");

            xmlSettings.pushTag("vertex", 0);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("vertex", 1);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 100.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("vertex", 2);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 100.0f), xmlSettings.getValue("y", 100.0f) ) );
            xmlSettings.popTag();

            xmlSettings.pushTag("vertex", 3);
            vertices.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 100.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.popTag(); // vertices
            
            xmlSettings.pushTag("texCoords");
            
            vector<ofVec2f> texCoords;
            
            xmlSettings.pushTag("texCoord", 0);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("texCoord", 1);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 1.0f), xmlSettings.getValue("y", 0.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.pushTag("texCoord", 2);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 1.0f), xmlSettings.getValue("y", 1.0f) ) );
            xmlSettings.popTag();

            xmlSettings.pushTag("texCoord", 3);
            texCoords.push_back( ofVec2f( xmlSettings.getValue("x", 0.0f), xmlSettings.getValue("y", 1.0f) ) );
            xmlSettings.popTag();
            
            xmlSettings.popTag(); // texCoords
            
            
            // now we have variables sourceName and sourceTexture
            // by checking those we can use one or another addSurface method
            if ( sourceName != "none" && sourceTexture != NULL ) {
                addSurface(ofxSurfaceType::QUAD_SURFACE, sourceTexture, vertices, texCoords);
            } else {
                addSurface(ofxSurfaceType::QUAD_SURFACE, vertices, texCoords);
            }
            
            xmlSettings.popTag(); // surface
        }
    }
    
    xmlSettings.popTag(); // surfaces
}

ofxBaseSurface* ofxSurfaceManager::selectSurface(int index)
{
    if ( index >= surfaces.size() ) {
        throw std::runtime_error("Surface index out of bounds.");
    }
    
    selectedSurface = surfaces[index];
    
    // notify that a new surface has been selected
    ofSendMessage("surfaceSelected");
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
    if ( !image->loadImage(path) ){
        return NULL;
    }
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



