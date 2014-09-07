#include "ofxRadioList.h"

ofxRadioList::ofxRadioList()
{
    bHasTitle = false;
    storedTitle = "";
    storedSelectedItem = 0;
}

ofxRadioList::ofxRadioList(vector<string> &labels)
{
    ofxRadioList();
    setup(labels);
}

ofxRadioList::ofxRadioList(string title, vector<string> &labels)
{
    ofxRadioList();
    setup(title, labels);
}

ofxRadioList::~ofxRadioList()
{
    clear();
}

void ofxRadioList::setup(vector<string> &labels)
{
    // Copy incomming labels for later use
    storedLabels = labels;
    
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
    // Store title for later use
    storedTitle = title;
    
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

void ofxRadioList::selectItem(int index)
{
    if (bHasTitle) {
        // We don't count the ofxLabel as an item, thus if title is set
        // items in guiGroup start from index 1
        index += 1;
    }
    
    if (index >= guiGroup.getNumControls()) {
        return;
    }
    
    unselectAll();
    
    ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(index));
    toggle->removeListener(this, &ofxRadioList::onToggleClicked);
    *toggle = true; // Select the specific radio button
    toggle->addListener(this, &ofxRadioList::onToggleClicked);
    string name = toggle->getName();
    ofNotifyEvent(radioSelectedEvent, name, this);
    
    storedSelectedItem = index;
}

void ofxRadioList::enable()
{
    if (guiGroup.getNumControls() >= 0) {
        clear();
    }
    
    // Rebuild everyting
    if (bHasTitle) {
        setup(storedTitle, storedLabels);
    } else {
        setup(storedLabels);
    }
    
    if (bHasTitle && storedSelectedItem == 0) {
        return;
    }
    
    // Select the stored selected item without throwing an event
    ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(storedSelectedItem));
    toggle->removeListener(this, &ofxRadioList::onToggleClicked);
    *toggle = true;
    toggle->addListener(this, &ofxRadioList::onToggleClicked);
}

void ofxRadioList::disable()
{
    // Just remove everything
    clear();
}

void ofxRadioList::clear()
{
    int i;
    for (i = 0; i < guiGroup.getNumControls(); i++) {
        if (bHasTitle && i == 0) {
            continue;
        }
        ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
        toggle->removeListener(this, &ofxRadioList::onToggleClicked);
    }
    guiGroup.clear();
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

string ofxRadioList::getItemName(int index)
{
    if (bHasTitle) {
        index += 1;
    }
    
    if (index >= guiGroup.getNumControls()) {
        return "";
    }
    
    ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(index));
    return toggle->getName();
}

int ofxRadioList::size()
{
    if (bHasTitle) {
        return guiGroup.getNumControls() - 1;
    } else {
        return guiGroup.getNumControls();
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
            /*
            toggle->removeListener(this, &ofxRadioList::onToggleClicked);
            *toggle = true; // Select the specific radio button
            toggle->addListener(this, &ofxRadioList::onToggleClicked);
            string name = toggle->getName();
            ofNotifyEvent(radioSelectedEvent, name, this);
            //cout << toggle->getName() << endl; // debug
            */
            if (bHasTitle) {
                selectItem(i - 1);
            } else {
                selectItem(i);
            }
            
            break;
        }
    }
}
