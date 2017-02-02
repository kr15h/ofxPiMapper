#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "DeselectTexCoordCmd.h"
#include "SelNextSurfaceCmd.h"
#include "TranslateCanvasCmd.h"
#include "SetTexMapDrawModeCmd.h"
#include "MvTexCoordCmd.h"
#include "MvAllTexCoordsCmd.h"
#include "SaveTexCoordPosCmd.h"
#include "SelTexCoordCmd.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class TextureMappingMode : public ApplicationBaseMode {

	public:
		static TextureMappingMode * instance();
	
		void setup(Application * app);
		void update(Application * app);
		void draw(Application * app);
	
		void onKeyPressed(Application * app, ofKeyEventArgs & args);
        void onBackgroundPressed(Application * app, GuiBackgroundEvent & e);
		void onMousePressed(Application * app, ofMouseEventArgs & args);
		void onMouseReleased(Application * app, ofMouseEventArgs & args);
		void onMouseDragged(Application * app, ofMouseEventArgs & args);
		void onGuiEvent(Application * app, GuiEvent & e){}

		void drawTexture(Application * app);
		void moveSelectedTexCoord(Application * app, ofVec2f by);
		void selectNextVertex(Application * app);
		void selectPrevVertex(Application * app);
	
		void setTranslation(ofPoint p);
		void setDrawMode(int m);
	
		ofPoint getTranslation();
	
		int getDrawMode();
		int getNextDrawMode();
		int getPrevDrawMode();

	private:
		static TextureMappingMode * _instance;
	
		TextureMappingMode();

		bool _bTranslateCanvas;
		bool _bCropAreaDrag;
	
		int _drawMode;
	
		ofPoint _clickPosition;
		ofPoint _canvasTranslate;
		ofPoint _prevCanvasTranslate;
		ofPoint _clickCanvasTranslate;
	
		ofVec2f _texCoordOnClick;

};

} // namespace piMapper
} // namespace ofx
