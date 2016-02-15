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

// TODO: compress the following structs into something like:
// struct GuiEvent{
//   ofMouseEventArgs args;
//   GuiObject obj;
// };
// It could be then possible to check the object in question
// to decide what to do next.
struct GuiJointEvent{
	ofMouseEventArgs args;
	int jointIndex;
};

struct GuiSurfaceEvent{
	ofMouseEventArgs args;
	BaseSurface * surface;
};

struct GuiBackgroundEvent{
	ofMouseEventArgs args;
};

class Gui {
	public:
		static Gui * instance();
	
		ofEvent <GuiEvent> event;
		void notifyEvent(ofMouseEventArgs & args);
	
		// TODO: combine the following events into one
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
	
		ofEvent <GuiBackgroundEvent> backgroundPressedEvent;
	
		void notifyBackgroundPressed(ofMouseEventArgs & args);
	
	private:
		static Gui * _instance;
};

} // piMapper
} // ofx