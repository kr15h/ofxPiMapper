#ifndef H_OFX_BASE_JOINT
#define H_OFX_BASE_JOINT

#include "ofMain.h"

class ofxBaseJoint {
public:
    ofxBaseJoint();
    ~ofxBaseJoint();
    
    void registerMouseEvents();
    void unregisterMouseEvents();
    
    ofVec2f position;
    bool enabled;
    bool visible;
    bool selected;
    
    void mousePressed(ofMouseEventArgs& args);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(ofMouseEventArgs& args);
    void startDrag();
    void stopDrag();
    void select();
    void unselect();
    bool isDragged();
    bool isSelected();
    
    virtual void update(){};
    virtual void draw(){};
    virtual bool hitTest(ofVec2f position){};
    
protected:
    ofColor fillColor;
    ofColor strokeColor;
    ofColor fillColorSelected;
    ofColor strokeColorSelected;
    float strokeWidth;
    ofVec2f clickDistance; // How far from the center of the joint the user has clicked?
    bool bDrag;
    
private:
    void setDefaultColors();
    void setDefaultProperties();
};

#endif
