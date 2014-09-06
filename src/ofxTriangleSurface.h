#ifndef H_OFX_TRIANGLE_SURFACE
#define H_OFX_TRIANGLE_SURFACE

#include "ofMain.h"
#include "ofxBaseSurface.h"
#include "ofxSurfaceType.h"

class ofxTriangleSurface : public ofxBaseSurface
{
public:
	ofxTriangleSurface();
	~ofxTriangleSurface();
    
    void setup();
    void setup( ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f t1, ofVec2f t2, ofVec2f t3, ofTexture* texturePtr );
    void draw();
    void setVertex( int index, ofVec2f p );
    void setTexCoord( int index, ofVec2f t );
    void moveBy(ofVec2f v);
    
    int getType();
    bool hitTest(ofVec2f p);
    ofVec2f getVertex(int index);
    ofVec2f getTexCoord(int index);
    ofPolyline getHitArea();
    ofPolyline getTextureHitArea();
    vector<ofVec3f>& getVertices();
    vector<ofVec2f>& getTexCoords();
};

#endif