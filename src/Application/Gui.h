#pragma once

#include "ofEvents.h"
#include "GuiEventType.h"
#include "BaseSurface.h"

namespace ofx {
namespace piMapper {

struct GuiEvent{
	ofMouseEventArgs args;
	int type;
};

struct GuiJointEvent{
	ofMouseEventArgs args;
	int jointIndex;
};

struct GuiSurfaceEvent{
	ofMouseEventArgs args;
	BaseSurface * surface;
};

class Gui {
	public:
		static Gui * instance();
	
		ofEvent <GuiEvent> event;
		void notifyEvent(ofMouseEventArgs & args);
	
		ofEvent <GuiJointEvent> jointPressedEvent;
		ofEvent <GuiJointEvent> jointReleasedEvent;
		ofEvent <GuiJointEvent> jointDraggedEvent;
	
		void notifyJointPressed(ofMouseEventArgs & args, int jointIndex);
		void notifyJointReleased(ofMouseEventArgs & args, int jointIndex);
		void notifyJointDragged(ofMouseEventArgs & args, int jointIndex);
	
		ofEvent <GuiSurfaceEvent> surfacePressedEvent;
		ofEvent <GuiSurfaceEvent> surfaceReleasedEvent;
		ofEvent <GuiSurfaceEvent> surfaceDraggedEvent;
	
		void notifySurfacePressed(ofMouseEventArgs & args, BaseSurface * surface);
		void notifySurfaceReleased(ofMouseEventArgs & args, BaseSurface * surface);
		void notifySurfaceDragged(ofMouseEventArgs & args, BaseSurface * surface);
	
	private:
		static Gui * _instance;
};

} // piMapper
} // ofx