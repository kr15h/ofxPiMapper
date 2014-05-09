#ifndef H_OFX_CIRCLE_JOINT
#define H_OFX_CIRCLE_JOINT

#include "ofMain.h"
#include "ofxBaseJoint.h"

class ofxCircleJoint : public ofxBaseJoint
{
public:
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
};

#endif