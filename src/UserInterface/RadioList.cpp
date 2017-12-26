#include "RadioList.h"

namespace ofx {
namespace piMapper {

RadioList::RadioList(){
	storedTitle = "";
	storedSelectedItem = 0;
}

RadioList::RadioList(std::vector<std::string> & labels, std::vector<std::string> & values){
	RadioList();
	setup(labels, values);
}

RadioList::RadioList(std::string title, std::vector<std::string> & labels, std::vector<std::string> & values){
	RadioList();
	setup(title, labels, values);
}

RadioList::~RadioList(){
	clear();
}

void RadioList::setup(std::vector<std::string> & labels, std::vector<std::string> & values){

	// Copy incomming labels for later use
	storedLabels = labels;
	storedValues = values;

	// Create toggles with labels from the labels arg
	int i;
	for(i = 0; i < labels.size(); i++){
		ofxToggle * toggle = new ofxToggle();
		toggle->setup(false);
		toggle->setName(labels[i]);
		toggle->addListener(this, &RadioList::onToggleClicked);
		guiGroup.add(toggle);
		#if OF_VERSION_MAJOR == 0 && (OF_VERSION_MINOR >= 8 && OF_VERSION_PATCH >= 2) || (OF_VERSION_MINOR >= 9 && OF_VERSION_PATCH >= 0)
			toggle->registerMouseEvents();
		#endif
	}
}

void RadioList::setup(std::string title, std::vector<std::string> & labels, std::vector<std::string> & values){

	// Store title for later use
	storedTitle = title;
	guiGroup.setName(title);
	setup(labels, values);
}

void RadioList::draw(){
	guiGroup.draw();
}

void RadioList::setTitle(std::string title){
	storedTitle = title;
	guiGroup.setName(title);
}

void RadioList::setPosition(ofPoint p){
	guiGroup.setPosition(p);
}

void RadioList::setPosition(float x, float y){
	guiGroup.setPosition(x, y);
}

void RadioList::selectItem(int index){
	if(index >= guiGroup.getNumControls()){
		return;
	}

	unselectAll();

	ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(index));
	toggle->removeListener(this, &RadioList::onToggleClicked);
	*toggle = true;          // Select the specific radio button
	toggle->addListener(this, &RadioList::onToggleClicked);
	//std::string name = toggle->getName();
	// Throw event with value that is image path instead of name
	std::string value = storedValues[index];
	ofNotifyEvent(onRadioSelected, value, this);
	storedSelectedItem = index;
}

bool RadioList::selectItemByValue(std::string itemValue){
	if(itemValue == ""){
		ofLogNotice("RadioList") << "Item value empty";
		return false;
	}
	unselectAll();
	int itemIndex = -1;
	for(int i = 0; i < storedValues.size(); i++){
		if(itemValue == storedValues[i]){
			itemIndex = i;
			break;
		}
	}
	if(itemIndex >= 0){
		ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(itemIndex));
		toggle->removeListener(this, &RadioList::onToggleClicked);
		*toggle = true;          // Select the specific radio button
		toggle->addListener(this, &RadioList::onToggleClicked);
		return true;
	}
	ofLogNotice("RadioList") << "Item with value " << itemValue << " not found";
	return false;
}

void RadioList::enable(){
	if(guiGroup.getNumControls() > 0){
		clear();
	}

	// Rebuild everyting
	setup(storedTitle, storedLabels, storedValues);

	// Select the stored selected item without throwing an event
	ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(storedSelectedItem));
	toggle->removeListener(this, &RadioList::onToggleClicked);
	*toggle = true;
	toggle->addListener(this, &RadioList::onToggleClicked);

	std::cout << "num items after enable: " << guiGroup.getNumControls() << std::endl;
}

void RadioList::disable(){
	// Just remove everything
	clear();
}

void RadioList::clear(){
	int i;
	for(i = 0; i < guiGroup.getNumControls(); i++){
		ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(i));
		toggle->removeListener(this, &RadioList::onToggleClicked);
		delete toggle;
	}
	guiGroup.clear();
}

void RadioList::unselectAll(){
	int i;
	for(i = 0; i < guiGroup.getNumControls(); i++){
		ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(i));
		ofParameter <bool> * paramPtr = static_cast <ofParameter <bool> *>(&toggle->getParameter());
		toggle->removeListener(this, &RadioList::onToggleClicked);
		*toggle = false;
		toggle->addListener(this, &RadioList::onToggleClicked);
	}
}

ofPoint RadioList::getPosition(){
	return guiGroup.getPosition();
}

float RadioList::getWidth(){
	return guiGroup.getWidth();
}

float RadioList::getHeight(){
	return guiGroup.getHeight();
}

std::string RadioList::getTitle(){
	return guiGroup.getName();
}

std::string RadioList::getItemName(int index){
	if(index >= guiGroup.getNumControls()){
		return "";
	}

	ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(index));
	return toggle->getName();
}

int RadioList::size(){
	return storedValues.size();
}

void RadioList::onToggleClicked(bool & toggleValue){
	unselectAll();

	// Search for the actual toggle triggering the event
	int i;
	for(i = 0; i < guiGroup.getNumControls(); i++){
		ofxToggle * toggle = static_cast <ofxToggle *>(guiGroup.getControl(i));
		ofParameter <bool> * paramPtr = static_cast <ofParameter <bool> *>(&toggle->getParameter());

		if(&(paramPtr->get()) == &toggleValue){
			selectItem(i);
			break;
		}
	}
}

} // namespace piMapper
} // namespace ofx
