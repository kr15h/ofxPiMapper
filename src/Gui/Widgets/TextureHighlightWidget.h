#pragma once

#include "GuiBaseWidget.h"
#include "SurfaceManager.h"
#include "BaseSurface.h"

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
		void findConsumerSurfaces();
	
	private:
		SurfaceManager * _sm;
	
		vector<BaseSurface *> _consumerSurfaces;
};

} // namespace piMapper
} // namespace ofx