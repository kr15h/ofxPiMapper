#include "RmSurfaceCmd.h"

namespace ofx {
namespace piMapper {

RmSurfaceCmd::RmSurfaceCmd(ofxPiMapper * app){
	_app = app;
	_surface = 0;
}

void RmSurfaceCmd::exec(){
	// Store the surface, this implies that the surfaceManager's
	// removeSelectedSurface does not destroy the surface.
	_surface = _app->surfaceManager.getSelectedSurface();
	_app->surfaceManager.removeSelectedSurface();
}

void RmSurfaceCmd::undo(){
	ofLogNotice("RmSurfaceCmd", "undo");
	if(_surface == 0){
		ofLogError("RmSurfaceCmd", "No surface stored");
	}
	_app->surfaceManager.addSurface(_surface);
	_app->surfaceManager.selectSurface(_surface);
	_surface = 0;
}

} // namespace piMapper
} // namespace ofx

