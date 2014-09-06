#include "ofxRadioList.h"

ofxRadioList::ofxRadioList(){}

ofxRadioList::ofxRadioList(vector<string> &labels)
{
    setup(labels);
}

ofxRadioList::~ofxRadioList()
{
    removeListeners();
    
    int i;
    for (i = 0; i < toggles.size(); i++) {
        delete toggles[i];
    }
    toggles.clear();
}

void ofxRadioList::setup(vector<string> &labels)
{
    // Create toggles with labels from the labels arg
    int i;
    for (i = 0; i < labels.size(); i++) {
        ofxToggle* toggle = new ofxToggle();
        toggle->setup(false);
        toggle->setName(labels[i]);
        toggle->setPosition(0, toggle->getHeight() * i);
        toggles.push_back(toggle);
    }
    
    addListeners();
}

void ofxRadioList::draw()
{
    int i;
    for (i = 0; i < toggles.size(); i++) {
        toggles[i]->draw();
    }
}

void ofxRadioList::addListeners()
{
    if (toggles.size() <= 0) return;
    
    int i;
    for (i = 0; i < toggles.size(); i++) {
        toggles[i]->addListener(this, &ofxRadioList::onToggleClicked);
    }
}

void ofxRadioList::removeListeners()
{
    if (toggles.size() <= 0) return;
    
    int i;
    for (i = 0; i < toggles.size(); i++) {
        toggles[i]->removeListener(this, &ofxRadioList::onToggleClicked);
    }
}

void ofxRadioList::unselectAll()
{
    int i;
    
    removeListeners();
    
    for (i = 0; i < toggles.size(); i++) {
        ofParameter<bool>* paramPtr = static_cast<ofParameter<bool>*>(&toggles[i]->getParameter());
        *toggles[i] = false;
    }
    
    addListeners();
}

void ofxRadioList::onToggleClicked(bool &toggleValue)
{
    unselectAll();
    
    // Search for the actual toggle triggering the event
    int i;
    for (i = 0; i < toggles.size(); i++) {
        ofParameter<bool>* paramPtr = static_cast<ofParameter<bool>*>(&toggles[i]->getParameter());
        
        if (&(paramPtr->get()) == &toggleValue) {
            removeListeners();
            *toggles[i] = true;
            cout << toggles[i]->getName() << endl;
            addListeners();
            break;
        }
    }
}
