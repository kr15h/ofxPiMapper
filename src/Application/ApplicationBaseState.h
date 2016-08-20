#pragma once

#include "ofEvents.h"
#include "ofLog.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class Application;

class ApplicationBaseState {

	public:
		virtual void draw(Application * app){}
		virtual void setState(Application * app, ApplicationBaseState * st);

		// Event handler virtual methods
		virtual void onKeyPressed(Application * app, ofKeyEventArgs & args){}
        virtual void onMousePressed(Application * app, ofMouseEventArgs & args){}
		virtual void onMouseReleased(Application * app, ofMouseEventArgs & args){}
		virtual void onMouseDragged(Application * app, ofMouseEventArgs & args){}
		virtual void onJointPressed(Application * app, GuiJointEvent & e){}
		virtual void onSurfacePressed(Application * app, GuiSurfaceEvent & e){}
		virtual void onBackgroundPressed(Application * app, GuiBackgroundEvent & e){}

};

} // namespace piMapper
} // namespace ofx
