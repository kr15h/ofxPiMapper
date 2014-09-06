#pragma once

#include "ofGraphics.h"
#include "ofxToggle.h"

class ofxRadioList
{
public:
    ofxRadioList();
    ofxRadioList(vector<string> &labels);
    ~ofxRadioList();
    
    void setup(vector<string> &labels);
    void draw();
    
private:
    vector<ofxToggle*> toggles;
    
    void addListeners();
    void removeListeners();
    void unselectAll();
    void onToggleClicked(bool &toggleValue);
};