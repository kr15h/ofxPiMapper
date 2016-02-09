#pragma once

#include "ofEvents.h"

namespace ofx {
namespace piMapper {

struct GuiEvent {
	ofMouseEventArgs args;
	int type;
};

class Gui {
	public:
		static Gui * instance();
	
		ofEvent <GuiEvent> event;
		void notifyEvent(ofMouseEventArgs & args);
	
	private:
		static Gui * _instance;
};

} // piMapper
} // ofx