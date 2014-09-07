#pragma once

#include "ofGraphics.h"
#include "ofxGuiGroup.h"
#include "ofxToggle.h"
#include "ofxLabel.h"

class ofxRadioList
{
public:
    ofxRadioList();
    ofxRadioList(vector<string> &labels);
    ofxRadioList(string title, vector<string> &labels);
    ~ofxRadioList();
    
    void setup(vector<string> &labels);
    void setup(string title, vector<string> &labels);
    void draw();
    void setTitle(string title);
    void setPosition(ofPoint p);
    void setPosition(float x, float y);
    ofPoint getPosition();
    float getWidth();
    float getHeight();
    string getTitle();
    string getItem(int index);
    
    // This event notifies about a toggle being selected and passes it's name to the listeners.
    // Use ofAddListener(ofxRadioListInstance.radioSelectedEvent, listenerClassPtr, &listenerClass::listenerMethod)
    // to listen to this. Listner method void listenerMethod(string & radioName)
    ofEvent<string> radioSelectedEvent;
    
private:
    ofxGuiGroup guiGroup;
    bool bHasTitle;
    
    void unselectAll();
    void onToggleClicked(bool &toggleValue);
};