#ifndef H_OFX_BASE_JOINT
#define H_OFX_BASE_JOINT

#include "ofMain.h"

class ofxBaseJoint {
public:
    ofxBaseJoint();
    ~ofxBaseJoint();
    
    virtual void mousePressed(ofMouseEventArgs& args){};
    virtual void mouseReleased(ofMouseEventArgs& args){};
    virtual void mouseDragged(ofMouseEventArgs& args){};
};

#endif
