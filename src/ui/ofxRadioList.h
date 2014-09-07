#pragma once

#include "ofGraphics.h"
#include "ofxGuiGroup.h"
#include "ofxToggle.h"

class ofxRadioList
{
public:
    ofxRadioList();
    ofxRadioList(vector<string> &labels);
    ~ofxRadioList();
    
    void setup(vector<string> &labels);
    void draw();
    void setPosition(ofPoint p);
    void setPosition(float x, float y);
    ofPoint getPosition();
    float getWidth();
    float getHeight();
    
    // This event notifies about a toggle being selected and passes it's name to the listeners
    // Use ofAddListener(ofxRadioListInstance.radioSelectedEvent, listenerClassPtr, &listenerClass::listenerMethod)
    // to listen to this. Listner method void listenerMethod(string & radioName)
    ofEvent<string> radioSelectedEvent;
    
private:
    ofxGuiGroup guiGroup;
    
    void unselectAll();
    void onToggleClicked(bool &toggleValue);
};