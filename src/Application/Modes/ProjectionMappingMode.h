#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "AddSurfaceCmd.h"
#include "RmSurfaceCmd.h"
#include "AddGridRowCmd.h"
#include "RmGridRowCmd.h"
#include "AddGridColCmd.h"
#include "RmGridColCmd.h"
#include "SelNextSurfaceCmd.h"
#include "SelPrevSurfaceCmd.h"
#include "SelNextVertexCmd.h"
#include "SelPrevVertexCmd.h"
#include "SelVertexCmd.h"
#include "SelSurfaceCmd.h"
#include "MvSelectionCmd.h"
#include "StartDragSurfaceCmd.h"
#include "TogglePerspectiveCmd.h"
#include "DeselectSurfaceCmd.h"
#include "SetNextSourceCmd.h"
#include "DuplicateSurfaceCmd.h"
#include "ToggleAnimatedSourceCmd.h"
#include "MvLayerUpCmd.h"
#include "MvLayerDnCmd.h"
#include "ScaleSurfaceFromToCmd.h"
#include "MvSurfaceVertCmd.h"
#include "SurfaceType.h"
#include "Gui.h"

#include "ScaleWidget.h"
//#include "LayerPanelWidget.h"

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

};

} // namespace piMapper
} // namespace ofx
