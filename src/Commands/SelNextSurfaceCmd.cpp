#include "SelNextSurfaceCmd.h"

namespace ofx {
namespace piMapper {

SelNextSurfaceCmd::SelNextSurfaceCmd(SurfaceManager * surfaceManager){
	_surfaceManager = surfaceManager;
}

void SelNextSurfaceCmd::exec(){
	ofLogNotice("SelNextSurfaceCmd", "exec");
	_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	_prevSelectedVertex = _surfaceManager->getSelectedVertexIndex();
	_surfaceManager->selectNextSurface();
}

void SelNextSurfaceCmd::undo(){
	ofLogNotice("SelNextSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_prevSelectedSurface);
	_surfaceManager->selectVertex(_prevSelectedVertex);
	_prevSelectedSurface = 0;
}

} // namespace piMapper
} // namespace ofx

