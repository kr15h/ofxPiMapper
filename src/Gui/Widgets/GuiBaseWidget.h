#pragma once

#include "ofEvents.h"

namespace ofx {
namespace piMapper {

struct GuiWidgetEvent{
	ofMouseEventArgs args;
};

class GuiBaseWidget {
	public:
		virtual void setup() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
	
		virtual void onMousePressed(ofMouseEventArgs & e) = 0;
		virtual void onMouseReleased(ofMouseEventArgs & e) = 0;
		virtual void onMouseDragged(ofMouseEventArgs & e) = 0;
	
		virtual bool inside(float x, float y) = 0;

		virtual float getScale(){ return 0.0f; }
	
		ofEvent <GuiWidgetEvent> guiWidgetEvent;
};

} // namespace piMapper
} // namespace ofx