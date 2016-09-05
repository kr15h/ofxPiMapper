#pragma once

#include "GuiBaseWidget.h"
#include "SurfaceManager.h"

namespace ofx {
namespace piMapper {

class LayerPanelWidget : public GuiBaseWidget {
	public:
		LayerPanelWidget();
	
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