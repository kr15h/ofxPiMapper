#include "DuplicateSurfaceCmd.h"

namespace ofx {
namespace piMapper {

DuplicateSurfaceCmd::DuplicateSurfaceCmd(BaseSurface * surface, SurfaceManager * surfaceManager){
	_surface = surface;
	_surfaceManager = surfaceManager;
}

void DuplicateSurfaceCmd::exec(){
	ofLogNotice("DuplicateSurfaceCmd", "exec");
	_duplicate = _surface->clone();
	_surfaceManager->addSurface(_duplicate);
	_duplicate->moveBy(ofVec2f(10.0f, 10.0f));
	_surfaceManager->selectSurface(_duplicate);
}

void DuplicateSurfaceCmd::undo(){
	ofLogNotice("DuplicateSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_surface);
	_surfaceManager->deleteSurface(_duplicate);
}

} // namespace piMapper
} // namespace ofx

