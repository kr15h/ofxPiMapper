#pragma once

#include "ofEvents.h"
#include "GuiEventType.h"
#include "BaseSurface.h"

#include "GuiBaseWidget.h"
#include "ScaleWidget.h"

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

struct GuiWidgetEvent{
	ofMouseEventArgs args;
	GuiBaseWidget * widget;
};

class Gui {
	public:
		static Gui * instance();
	
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
	
		ScaleWidget & getScaleWidget();
		ofEvent <GuiWidgetEvent> guiWidgetEvent;
		void notifyGuiWidgetEvent(ofMouseEventArgs & args, GuiBaseWidget * widget);
	
		void onMousePressed(ofMouseEventArgs & args);
		void onMouseReleased(ofMouseEventArgs & args);
		void onMouseDragged(ofMouseEventArgs & args);
	
	private:
		static Gui * _instance;
	
		ScaleWidget _scaleWidget;
};

} // piMapper
} // ofx