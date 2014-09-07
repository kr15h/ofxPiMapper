#include "ofxRadioList.h"

ofxRadioList::ofxRadioList(){}

ofxRadioList::ofxRadioList(vector<string> &labels)
{
    setup(labels);
}

ofxRadioList::~ofxRadioList()
{

    int i;
    for (i = 0; i < guiGroup.getNumControls(); i++) {
        ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
        toggle->removeListener(this, &ofxRadioList::onToggleClicked);
    }
}

void ofxRadioList::setup(vector<string> &labels)
{
    // Create toggles with labels from the labels arg
    int i;
    for (i = 0; i < labels.size(); i++) {
        ofxToggle* toggle = new ofxToggle();
        toggle->setup(false);
        toggle->setName(labels[i]);
        toggle->addListener(this, &ofxRadioList::onToggleClicked);
        guiGroup.add(toggle);
    }
}

void ofxRadioList::draw()
{
    guiGroup.draw();
}

void ofxRadioList::setPosition(ofPoint p)
{
    guiGroup.setPosition(p);
}

void ofxRadioList::setPosition(float x, float y)
{
    guiGroup.setPosition(x, y);
}

ofPoint ofxRadioList::getPosition()
{
    return guiGroup.getPosition();
}

float ofxRadioList::getWidth()
{
    return guiGroup.getWidth();
}

float ofxRadioList::getHeight()
{
    return guiGroup.getHeight();
}

void ofxRadioList::unselectAll()
{
    int i;
    for (i = 0; i < guiGroup.getNumControls(); i++) {
        ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
        ofParameter<bool>* paramPtr = static_cast<ofParameter<bool>*>(&toggle->getParameter());
        toggle->removeListener(this, &ofxRadioList::onToggleClicked);
        *toggle = false;
        toggle->addListener(this, &ofxRadioList::onToggleClicked);
    }
}

void ofxRadioList::onToggleClicked(bool &toggleValue)
{
    unselectAll();
    
    // Search for the actual toggle triggering the event
    int i;
    for (i = 0; i < guiGroup.getNumControls(); i++) {
        ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
        ofParameter<bool>* paramPtr = static_cast<ofParameter<bool>*>(&toggle->getParameter());
        
        if (&(paramPtr->get()) == &toggleValue) {
            toggle->removeListener(this, &ofxRadioList::onToggleClicked);
            *toggle = true; // Select the specific radio button
            toggle->addListener(this, &ofxRadioList::onToggleClicked);
            string name = toggle->getName();
            ofNotifyEvent(radioSelectedEvent, name, this);
            //cout << toggle->getName() << endl; // debug
            break;
        }
    }
}
