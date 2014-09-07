#ifndef H_OFX_SURFACE_MANAGER
#define H_OFX_SURFACE_MANAGER

#include "ofxBaseSurface.h"
#include "ofxTriangleSurface.h"
#include "ofxQuadSurface.h"
#include "ofxSurfaceType.h"
#include "ofEvents.h"
#include "ofxXmlSettings.h"

using namespace std;

class ofxSurfaceManager
{
public:
    ofxSurfaceManager();
    ~ofxSurfaceManager();
    
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
    
    ofxBaseSurface* getSurface(int index);
    int size();
    ofxBaseSurface* selectSurface(int index);
    ofxBaseSurface* getSelectedSurface();
    void deselectSurface();
    ofTexture* loadImageSource(string name, string path);
    string getSelectedSurfaceSourceName();
    string getSurfaceSourceName( ofxBaseSurface* surface );
    
private:
    vector<ofxBaseSurface*> surfaces;
    ofxBaseSurface* selectedSurface;
    vector<string> loadedImageSourceNames;
    vector<ofImage*> loadedImageSources;
    ofxXmlSettings xmlSettings;
    
};

#endif