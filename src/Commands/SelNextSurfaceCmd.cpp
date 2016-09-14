#include "SelNextSurfaceCmd.h"

namespace ofx {
namespace piMapper {

SelNextSurfaceCmd::SelNextSurfaceCmd(SurfaceManager * surfaceManager){
	_surfaceManager = surfaceManager;
}

void SelNextSurfaceCmd::exec(){
	_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	_surfaceManager->selectNextSurface();
}

void SelNextSurfaceCmd::undo(){
	ofLogNotice("SelNextSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_prevSelectedSurface);
	_prevSelectedSurface = 0;
}

} // namespace piMapper
} // namespace ofx

