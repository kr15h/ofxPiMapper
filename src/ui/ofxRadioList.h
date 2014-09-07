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
    void selectItem(int index);
    void enable();
    void disable();
    void clear();
    void unselectAll();
    ofPoint getPosition();
    float getWidth();
    float getHeight();
    string getTitle();
    string getItemName(int index);
    int size();
    
    // This event notifies about a toggle being selected and passes it's name to the listeners.
    // Use ofAddListener(ofxRadioListInstance.radioSelectedEvent, listenerClassPtr, &listenerClass::listenerMethod)
    // to listen to this. Listner method void listenerMethod(string & radioName)
    ofEvent<string> radioSelectedEvent;
    
private:
    vector<string> storedLabels;
    string storedTitle;
    ofxGuiGroup guiGroup;
    int storedSelectedItem;
    
    void onToggleClicked(bool &toggleValue);
};