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
		RadioList(vector <string> & labels, vector <string> & values);
		RadioList(string title, vector <string> & labels, vector <string> & values);
		~RadioList();

		void setup(vector <string> & labels, vector <string> & values);
		void setup(string title, vector <string> & labels, vector <string> & values);
		void draw();
		void setTitle(string title);
		void setPosition(ofPoint p);
		void setPosition(float x, float y);
		void selectItem(int index);
		bool selectItemByValue(string itemValue);
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

		// This event notifies about a toggle being selected and passes it's name to
		// the listeners.
		// Use ofAddListener(RadioListInstance.radioSelectedEvent, listenerClassPtr,
		// &listenerClass::listenerMethod)
		// to listen to this. Listner method void listenerMethod(string & radioName)
		ofEvent <string> onRadioSelected;

	private:
		vector <string> storedLabels;
		vector <string> storedValues;
		string storedTitle;
		ofxGuiGroup guiGroup;
		int storedSelectedItem;

		void onToggleClicked(bool & toggleValue);

};

} // namespace piMapper
} // namespace ofx