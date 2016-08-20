#pragma once

#include "ofRectangle.h"
#include "ofPolyline.h"
#include "GuiBaseWidget.h"
#include "ofGraphics.h"
//#include "Gui.h"

namespace ofx {
namespace piMapper {

class ScaleWidget : public GuiBaseWidget {
	public:
		ScaleWidget();
	
		void setup();
		void update();
		void draw();
	
		void onMousePressed(ofMouseEventArgs & args);
		void onMouseReleased(ofMouseEventArgs & args);
		void onMouseDragged(ofMouseEventArgs & args);
	
		bool inside(float x, float y);
	
		// This should be the size of the objet's bounding box
		void setRect(ofRectangle rect);

	private:
		ofRectangle _handle;
	
		ofPolyline _line;
	
		bool _dragging;
};

} // namespace piMapper
} // namespace ofx