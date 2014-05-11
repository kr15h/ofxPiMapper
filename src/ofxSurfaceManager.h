#ifndef H_OFX_SURFACE_MANAGER
#define H_OFX_SURFACE_MANAGER

#include "ofMain.h"
#include "ofxTriangleSurface.h"
#include "ofxSurfaceGui.h"

class ofxSurfaceManager
{
public:
    ofxSurfaceManager();
    ~ofxSurfaceManager();
    
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    
    void addSurface();
    void addSurface(ofTexture* texturePtr);
    void addSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3);
    void addSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3, ofTexture* texturePtr);
    
    void removeSurface(int index);
    void setGuiMode(ofxSurfaceGui::editMode);
    void selectSurface(int index);
    void unselectAllSurfaces();
    int size();
    
private:
    deque<ofxTriangleSurface*> triangleSurfaces;
    deque<ofxSurfaceGui*> surfaceGuis;
    
    void addTriangleSurface();
    void addTriangleSurface(ofTexture* texturePtr);
    void addTriangleSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3);
    void addTriangleSurface(ofVec2f v1, ofVec2f v2, ofVec2f v3, ofVec2f t1, ofVec2f t2, ofVec2f t3, ofTexture* texturePtr);
};

#endif