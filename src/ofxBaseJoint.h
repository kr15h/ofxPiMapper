#ifndef H_OFX_BASE_JOINT
#define H_OFX_BASE_JOINT

#include "ofMain.h"

class ofxBaseJoint {
public:
    ofxBaseJoint();
    ~ofxBaseJoint();
    
    ofVec2f position;
    bool enabled;
    bool visible;
    bool selected;
    
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(ofMouseEventArgs& args);
    void mouseDragged(ofMouseEventArgs& args);
    void startDrag();
    void stopDrag();
    
    virtual void update(ofEventArgs& args){};
    virtual void draw(ofEventArgs& args){};
    virtual bool hitTest(ofVec2f position){};
    
protected:
    ofColor fillColor;
    ofColor strokeColor;
    ofVec2f clickDistance;
    bool dragging;
    
private:
    void setDefaultColors();
    void setDefaultProperties();
    void registerAppEvents();
    void unregisterAppEvents();
    void registerMouseEvents();
    void unregisterMouseEvents();
};

#endif
