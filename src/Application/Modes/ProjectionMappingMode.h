#pragma once

#include "Application.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "StartDragSurfaceCmd.h"
#include "DeselectSurfaceCmd.h"
#include "MvSurfaceVertCmd.h"
#include "SurfaceType.h"
#include "Gui.h"
#include "ScaleWidget.h"

namespace ofx {
namespace piMapper {

class ProjectionMappingMode : public ApplicationBaseMode {

	public:
		static ProjectionMappingMode * instance();
	
		void setup(Application * app);
		void update(Application * app);
		void draw(Application * app);
		void onKeyPressed(Application * app, ofKeyEventArgs & args);
		void onMousePressed(Application * app, ofMouseEventArgs & args);
		void onMouseReleased(Application * app, ofMouseEventArgs & args);
		void onMouseDragged(Application * app, ofMouseEventArgs & args);
		void onJointPressed(Application * app, GuiJointEvent & e);
		void onSurfacePressed(Application * app, GuiSurfaceEvent & e);
		void onBackgroundPressed(Application * app, GuiBackgroundEvent & e);
	
		void onGuiEvent(Application * app, GuiEvent & e);

	private:
		ProjectionMappingMode();
	
		static ProjectionMappingMode * _instance;
	
		float _surfaceScaleBeforeTransform;
	
		ofVec2f _clickPosition;
	
		bool _bSurfaceDrag;
		bool _bDrawLayerPanel;

};

} // namespace piMapper
} // namespace ofx
