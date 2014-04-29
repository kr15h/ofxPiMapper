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
    void setup( ofVec2f p1, ofVec2f p2, ofVec2f p3 );
    void draw();
};

#endif