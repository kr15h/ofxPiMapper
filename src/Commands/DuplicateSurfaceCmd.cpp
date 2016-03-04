#include "DuplicateSurfaceCmd.h"

namespace ofx {
namespace piMapper {

DuplicateSurfaceCmd::DuplicateSurfaceCmd(BaseSurface * surface, SurfaceManager * surfaceManager){
	_surface = surface;
	_surfaceManager = surfaceManager;
}

void DuplicateSurfaceCmd::exec(){
	//_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	//_surfaceManager->selectPrevSurface();
	_surfaceManager->duplicateSurface(_surface);
}

void DuplicateSurfaceCmd::undo(){
	ofLogNotice("DuplicateSurfaceCmd", "undo");
	//_surfaceManager->selectSurface(_prevSelectedSurface);
	//_prevSelectedSurface = 0;
	//_surfaceManager->d
}

} // namespace piMapper
} // namespace ofx

