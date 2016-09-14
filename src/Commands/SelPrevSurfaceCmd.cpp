#include "SelPrevSurfaceCmd.h"

namespace ofx {
namespace piMapper {

SelPrevSurfaceCmd::SelPrevSurfaceCmd(SurfaceManager * surfaceManager){
	_surfaceManager = surfaceManager;
}

void SelPrevSurfaceCmd::exec(){
	_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	_surfaceManager->selectPrevSurface();
}

void SelPrevSurfaceCmd::undo(){
	ofLogNotice("SelPrevSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_prevSelectedSurface);
	_prevSelectedSurface = 0;
}

} // namespace piMapper
} // namespace ofx

