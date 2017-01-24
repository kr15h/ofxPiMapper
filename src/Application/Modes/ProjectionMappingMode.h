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
#include "ToggleAnimatedSourceCmd.h"
#include "ScaleSurfaceFromToCmd.h"
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
	
		// Undoable public methods
		void selectSurface(Application * app, int i);
		void selectNextSurface(Application * app);
		void selectPrevSurface(Application * app);
		void selectNextVertex(Application * app);
		void selectPrevVertex(Application * app);
		void moveSelection(Application * app, ofVec2f by);
		void createSurface(Application * app, SurfaceType type);

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
