#pragma once

#include "GuiBaseWidget.h"
#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

class TextureHighlightWidget : public GuiBaseWidget {
	public:
		TextureHighlightWidget();
	
		void setup(){}
		void update(){}
		void draw();
	
		void onMousePressed(ofMouseEventArgs & args){}
		void onMouseReleased(ofMouseEventArgs & args){}
		void onMouseDragged(ofMouseEventArgs & args){}
	
		bool inside(float x, float y){ return false; }
	
		void setSurfaceManager(SurfaceManager * sm){ _sm = sm; }
	
	private:
		SurfaceManager * _sm;
};

} // namespace piMapper
} // namespace ofx