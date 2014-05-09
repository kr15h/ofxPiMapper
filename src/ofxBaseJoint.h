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
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void startDrag();
    void stopDrag();
    bool isDragged();
    
    virtual void update(){};
    virtual void draw(){};
    virtual bool hitTest(ofVec2f position){};
    
protected:
    ofColor fillColor;
    ofColor strokeColor;
    float strokeWidth;
    ofVec2f clickDistance;
    bool dragging;
    
private:
    void setDefaultColors();
    void setDefaultProperties();
};

#endif
