#ifndef H_OFX_TRIANGLE_SURFACE
#define H_OFX_TRIANGLE_SURFACE

#include "ofMain.h"
#include "ofxBaseSurface.h"

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
};

#endif