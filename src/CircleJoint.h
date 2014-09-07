#ifndef H_OFX_CIRCLE_JOINT
#define H_OFX_CIRCLE_JOINT

#include "ofMain.h"
#include "ofxBaseJoint.h"

class ofxCircleJoint : public ofxBaseJoint
{
public:
    ofxCircleJoint();
    
    void update();
    void draw();
    bool hitTest(ofVec2f position);
    
private:
    float radius;
    
    void setDefaultProperties();
};

#endif