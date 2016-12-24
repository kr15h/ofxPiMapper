#include "SelPrevSurfaceCmd.h"

namespace ofx {
namespace piMapper {

SelPrevSurfaceCmd::SelPrevSurfaceCmd(SurfaceManager * surfaceManager){
	_surfaceManager = surfaceManager;
}

void SelPrevSurfaceCmd::exec(){
	_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	_prevSelectedVertex = _surfaceManager->getSelectedVertexIndex();
	_surfaceManager->selectPrevSurface();
}

void SelPrevSurfaceCmd::undo(){
	ofLogNotice("SelPrevSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_prevSelectedSurface);
	_surfaceManager->selectVertex(_prevSelectedVertex);
	_prevSelectedSurface = 0;
}

} // namespace piMapper
} // namespace ofx

