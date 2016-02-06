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
#include "MvSelectionCmd.h"
#include "TogglePerspectiveCmd.h"
#include "SurfaceType.h"

namespace ofx {
namespace piMapper {

class ProjectionMappingState : public ApplicationBaseState {

	public:
		static ProjectionMappingState * instance();
		void draw(Application * app);
		void onKeyPressed(Application * app, ofKeyEventArgs & args);

	private:
		static ProjectionMappingState * _instance;

};

} // namespace piMapper
} // namespace ofx
