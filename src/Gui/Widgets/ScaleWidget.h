#pragma once

#include "ofRectangle.h"
#include "ofPolyline.h"
#include "GuiBaseWidget.h"
#include "ofGraphics.h"
#include "BaseSurface.h"
#include "SurfaceManager.h"

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
		void setSurfaceManager(SurfaceManager * sm);

		float getScale(){
			return _scale;
		}

	private:
		ofRectangle _handle;
	
		ofPolyline _line;

		float _scale;
	
		bool _dragging;
	
		BaseSurface * _selectedSurface;
		SurfaceManager * _surfaceManager;
	
		void setRect(ofRectangle rect);
};

} // namespace piMapper
} // namespace ofx