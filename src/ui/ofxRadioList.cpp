#include "ofxRadioList.h"

ofxRadioList::ofxRadioList()
{
    bHasTitle = false;
}

ofxRadioList::ofxRadioList(vector<string> &labels)
{
    bHasTitle = false;
    setup(labels);
}

ofxRadioList::ofxRadioList(string title, vector<string> &labels)
{
    bHasTitle = false;
    setup(title, labels);
}

ofxRadioList::~ofxRadioList()
{
    int i;
    for (i = 0; i < guiGroup.getNumControls(); i++) {
        if (bHasTitle && i == 0) {
            continue;
        }
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

void ofxRadioList::setup(string title, vector<string> &labels)
{
    ofxLabel* label = new ofxLabel(title);
    guiGroup.add(label);
    bHasTitle = true;
    setup(labels);
}

void ofxRadioList::draw()
{
    guiGroup.draw();
}

void ofxRadioList::setTitle(string title)
{
    if (bHasTitle) {
        ofxLabel* label = static_cast<ofxLabel*>(guiGroup.getControl(0));
        label->setup(title);
    } else {
        ofxLabel* label = new ofxLabel(title);
        vector<ofxToggle*> toggles;
        int i;
        for (i = 0; i < guiGroup.getNumControls(); i++) {
            ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
            toggles.push_back(toggle);
        }
        guiGroup.clear();
        guiGroup.add(label);
        bHasTitle = true;
        for (i = 0; i < toggles.size(); i++) {
            guiGroup.add(toggles[i]);
        }
    }
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

string ofxRadioList::getTitle()
{
    if (bHasTitle) {
        ofxLabel* label = static_cast<ofxLabel*>(guiGroup.getControl(0));
        ofParameter<string>* parameter = static_cast<ofParameter<string>*>(&label->getParameter());
        return parameter->get();
    } else {
        return "";
    }
}

void ofxRadioList::unselectAll()
{
    int i;
    for (i = 0; i < guiGroup.getNumControls(); i++) {
        if (bHasTitle && i == 0) {
            continue;
        }
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
        if (bHasTitle && i == 0) {
            continue;
        }
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
