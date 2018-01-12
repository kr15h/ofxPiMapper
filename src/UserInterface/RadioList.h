#pragma once

#include "ofGraphics.h"
#include "ofxGuiGroup.h"
#include "ofxToggle.h"
#include "ofxLabel.h"

namespace ofx {
namespace piMapper {

class RadioList {
	public:
		RadioList();
		RadioList(std::vector<std::string> & labels, std::vector<std::string> & values);
		RadioList(std::string title, std::vector<std::string> & labels, std::vector<std::string> & values);
		~RadioList();

		void setup(std::vector<std::string> & labels, std::vector<std::string> & values);
		void setup(std::string title, std::vector<std::string> & labels, std::vector<std::string> & values);
		void draw();
		void setTitle(std::string title);
		void setPosition(ofPoint p);
		void setPosition(float x, float y);
		void selectItem(int index);
		bool selectItemByValue(std::string itemValue);
		void enable();
		void disable();
		void clear();
		void unselectAll();
		ofPoint getPosition();
		float getWidth();
		float getHeight();
		std::string getTitle();
		std::string getItemName(int index);
		int size();

		// This event notifies about a toggle being selected and passes it's name to
		// the listeners.
		// Use ofAddListener(RadioListInstance.radioSelectedEvent, listenerClassPtr,
		// &listenerClass::listenerMethod)
		// to listen to this. Listner method void listenerMethod(std::string & radioName)
		ofEvent <std::string> onRadioSelected;

	private:
		std::vector<std::string> storedLabels;
		std::vector<std::string> storedValues;
		std::string storedTitle;
		ofxGuiGroup guiGroup;
		int storedSelectedItem;

		void onToggleClicked(bool & toggleValue);

};

} // namespace piMapper
} // namespace ofx