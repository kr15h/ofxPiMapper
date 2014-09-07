#pragma once

#include "BaseSurface.h"
#include "TriangleSurface.h"
#include "QuadSurface.h"
#include "SurfaceType.h"

#include "ofEvents.h"
#include "ofxXmlSettings.h"

using namespace std;


namespace ofx{
    namespace piMapper{
class SurfaceManager
{
public:
    SurfaceManager();
    ~SurfaceManager();
    
    void draw();
    void addSurface(int surfaceType);
    void addSurface(int surfaceType, ofTexture* texturePtr);
    void addSurface(int surfaceType, vector<ofVec2f> vertices, vector<ofVec2f> texCoords);
    void addSurface(int surfaceType, ofTexture* texturePtr, vector<ofVec2f> vertices, vector<ofVec2f> texCoords);
    void removeSelectedSurface();
    void manageMemory(); // deletes unasigned sources
    void clear();
    void saveXmlSettings(string fileName);
    void loadXmlSettings(string fileName);
    
    BaseSurface* getSurface(int index);
    int size();
    BaseSurface* selectSurface(int index);
    BaseSurface* getSelectedSurface();
    void deselectSurface();
    ofTexture* loadImageSource(string name, string path);
    string getSelectedSurfaceSourceName();
    string getSurfaceSourceName( BaseSurface* surface );
    
private:
    vector<BaseSurface*> surfaces;
    BaseSurface* selectedSurface;
    vector<string> loadedImageSourceNames;
    vector<ofImage*> loadedImageSources;
    ofxXmlSettings xmlSettings;
    
};

    }}