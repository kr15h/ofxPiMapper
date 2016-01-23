#include "RmSurfaceCmd.h"

namespace ofx {
namespace piMapper {

RmSurfaceCmd::RmSurfaceCmd(SurfaceManager * sm){
	_surfaceManager = sm;
	_surface = 0;
}

void RmSurfaceCmd::exec(){
	// Store the surface, this implies that the surfaceManager's
	// removeSelectedSurface does not destroy the surface.
	_surface = _surfaceManager->getSelectedSurface();
	_surfaceManager->removeSelectedSurface();
}

void RmSurfaceCmd::undo(){
	ofLogNotice("RmSurfaceCmd", "undo");
	if(_surface == 0){
		ofLogError("RmSurfaceCmd", "No surface stored");
	}
	_surfaceManager->addSurface(_surface);
	_surfaceManager->selectSurface(_surface);
	_surface = 0;
}

} // namespace piMapper
} // namespace ofx

