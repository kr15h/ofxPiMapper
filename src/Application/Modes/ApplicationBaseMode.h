#pragma once

#include "ofEvents.h"
#include "ofLog.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class Application;

class ApplicationBaseMode {

	public:
		virtual void setup(Application * app){}
		virtual void update(Application * app){}
		virtual void draw(Application * app){}
		virtual void setState(Application * app, ApplicationBaseMode * st);

		// Event handler virtual methods
		virtual void onKeyPressed(Application * app, ofKeyEventArgs & args){}
        virtual void onMousePressed(Application * app, ofMouseEventArgs & args){}
		virtual void onMouseReleased(Application * app, ofMouseEventArgs & args){}
		virtual void onMouseDragged(Application * app, ofMouseEventArgs & args){}
		virtual void onJointPressed(Application * app, GuiJointEvent & e){}
		virtual void onSurfacePressed(Application * app, GuiSurfaceEvent & e){}
		virtual void onBackgroundPressed(Application * app, GuiBackgroundEvent & e){}
	
		virtual void onGuiEvent(Application * app, GuiEvent & e) = 0;
	
		// These are only used by TextureMappingMode for now.
		virtual ofPoint getTranslation(){ return ofPoint(0, 0); }
		virtual void setTranslation(ofPoint p){}

};

} // namespace piMapper
} // namespace ofx
