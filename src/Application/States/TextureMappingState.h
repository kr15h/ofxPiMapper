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
#include "TranslateCanvasCmd.h"
#include "SetTexMapDrawModeCmd.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class TextureMappingState : public ApplicationBaseState {

	public:
		static TextureMappingState * instance();
	
		void update(Application * app);
		void draw(Application * app);
		void onKeyPressed(Application * app, ofKeyEventArgs & args);
		void onKeyReleased(Application * app, ofKeyEventArgs & args);
        void onBackgroundPressed(Application * app, GuiBackgroundEvent & e);
		void onMousePressed(Application * app, ofMouseEventArgs & args);
		void onMouseReleased(Application * app, ofMouseEventArgs & args);
		void onMouseDragged(Application * app, ofMouseEventArgs & args);
		void drawTexture(Application * app);
	
		void onGuiEvent(Application * app, GuiEvent & e){}
	
		ofPoint getTranslation();
		void setTranslation(ofPoint p);

		void setDrawMode(int m);
		int getDrawMode();
		int getNextDrawMode();
		int getPrevDrawMode();

	private:
		static TextureMappingState * _instance;
	
		TextureMappingState();

		bool _bTranslateCanvas;
	
		int _drawMode;
	
		ofPoint _clickPosition;
		ofPoint _canvasTranslate;
		ofPoint _prevCanvasTranslate; // Canvas translate before TranslateCanvasCmd command exec
		ofPoint _clickCanvasTranslate;

};

} // namespace piMapper
} // namespace ofx
