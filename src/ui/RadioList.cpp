#include "RadioList.h"

namespace ofx {
namespace piMapper {
RadioList::RadioList() {
  storedTitle = "";
  storedSelectedItem = 0;
}

RadioList::RadioList(vector<string>& labels) {
  RadioList();
  setup(labels);
}

RadioList::RadioList(string title, vector<string>& labels) {
  RadioList();
  setup(title, labels);
}

RadioList::~RadioList() { clear(); }

void RadioList::setup(vector<string>& labels) {
  // Copy incomming labels for later use
  storedLabels = labels;

  // Create toggles with labels from the labels arg
  int i;
  for (i = 0; i < labels.size(); i++) {
    ofxToggle* toggle = new ofxToggle();
    toggle->setup(false);
    toggle->setName(labels[i]);
    toggle->addListener(this, &RadioList::onToggleClicked);
    guiGroup.add(toggle);
#if OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR >= 8 && OF_VERSION_PATCH >= 2
    toggle->registerMouseEvents();
#endif
  }
  
  cout << "num items: " << guiGroup.getNumControls() << endl;
}

void RadioList::setup(string title, vector<string>& labels) {
  // Store title for later use
  storedTitle = title;
  guiGroup.setName(title);
  setup(labels);
}

void RadioList::draw() { guiGroup.draw(); }

void RadioList::setTitle(string title) {
  storedTitle = title;
  guiGroup.setName(title);
}

void RadioList::setPosition(ofPoint p) { guiGroup.setPosition(p); }

void RadioList::setPosition(float x, float y) { guiGroup.setPosition(x, y); }

void RadioList::selectItem(int index) {
  if (index >= guiGroup.getNumControls()) {
    return;
  }

  unselectAll();

  ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(index));
  toggle->removeListener(this, &RadioList::onToggleClicked);
  *toggle = true;  // Select the specific radio button
  toggle->addListener(this, &RadioList::onToggleClicked);
  string name = toggle->getName();
  ofNotifyEvent(radioSelectedEvent, name, this);

  storedSelectedItem = index;
}

void RadioList::enable() {
  if (guiGroup.getNumControls() >= 0) {
    clear();
  }

  // Rebuild everyting
  setup(storedTitle, storedLabels);

  // Select the stored selected item without throwing an event
  ofxToggle* toggle =
      static_cast<ofxToggle*>(guiGroup.getControl(storedSelectedItem));
  toggle->removeListener(this, &RadioList::onToggleClicked);
  *toggle = true;
  toggle->addListener(this, &RadioList::onToggleClicked);

  cout << "num items after enable: " << guiGroup.getNumControls() << endl;
}

void RadioList::disable() {
  // Just remove everything
  clear();
}

void RadioList::clear() {
  int i;
  for (i = 0; i < guiGroup.getNumControls(); i++) {
    ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
    toggle->removeListener(this, &RadioList::onToggleClicked);
    delete toggle;
  }
  guiGroup.clear();
}

void RadioList::unselectAll() {
  int i;
  for (i = 0; i < guiGroup.getNumControls(); i++) {
    ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
    ofParameter<bool>* paramPtr =
        static_cast<ofParameter<bool>*>(&toggle->getParameter());
    toggle->removeListener(this, &RadioList::onToggleClicked);
    *toggle = false;
    toggle->addListener(this, &RadioList::onToggleClicked);
  }
}

ofPoint RadioList::getPosition() { return guiGroup.getPosition(); }

float RadioList::getWidth() { return guiGroup.getWidth(); }

float RadioList::getHeight() { return guiGroup.getHeight(); }

string RadioList::getTitle() { return guiGroup.getName(); }

string RadioList::getItemName(int index) {
  if (index >= guiGroup.getNumControls()) {
    return "";
  }

  ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(index));
  return toggle->getName();
}

int RadioList::size() { return guiGroup.getNumControls(); }

void RadioList::onToggleClicked(bool& toggleValue)
{
  unselectAll();

  // Search for the actual toggle triggering the event
  int i;
  for (i = 0; i < guiGroup.getNumControls(); i++) {
    ofxToggle* toggle = static_cast<ofxToggle*>(guiGroup.getControl(i));
    ofParameter<bool>* paramPtr =
        static_cast<ofParameter<bool>*>(&toggle->getParameter());

    if (&(paramPtr->get()) == &toggleValue) {
      selectItem(i);
      break;
    }
  }
}
}
}
