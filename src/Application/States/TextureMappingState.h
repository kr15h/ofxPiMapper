#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "SelNextTexCoordCmd.h"
#include "SelPrevTexCoordCmd.h"
#include "DeselectTexCoordCmd.h"
#include "SetNextSourceCmd.h"
#include "SelNextSurfaceCmd.h"
#include "ToggleAnimatedSourceCmd.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class TextureMappingState : public ApplicationBaseState {

	public:
		static TextureMappingState * instance();
		void draw(Application * app);
		void onKeyPressed(Application * app, ofKeyEventArgs & args);
        void onBackgroundPressed(Application * app, GuiBackgroundEvent & e);
		void onMousePressed(Application * app, ofMouseEventArgs & args);
		void onMouseReleased(Application * app, ofMouseEventArgs & args);
		void onMouseDragged(Application * app, ofMouseEventArgs & args);
	
		void onGuiEvent(Application * app, GuiEvent & e){}
	
		ofPoint getTranslation();
		void setTranslation(ofPoint p);

	private:
		static TextureMappingState * _instance;
	
		TextureMappingState();

		bool _bTranslateCanvas;
	
		ofPoint _clickPosition;
		ofPoint _canvasTranslate;
		ofPoint _clickCanvasTranslate;

};

} // namespace piMapper
} // namespace ofx
