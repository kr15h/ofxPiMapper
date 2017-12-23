#include "StartDragSurfaceCmd.h"

namespace ofx {
namespace piMapper {

StartDragSurfaceCmd::StartDragSurfaceCmd(BaseSurface * surface){
	_surface = surface;
}

void StartDragSurfaceCmd::exec(){
	ofLogNotice("StartDragSurfaceCmd", "exec");
	_previousVertices = _surface->getVertices();
	_surface->setMoved(false);
}

void StartDragSurfaceCmd::undo(){
	ofLogNotice("StartDragSurfaceCmd", "undo");
	ofVec3f step = _previousVertices[0] - _surface->getVertices()[0];
	_surface->moveBy(Vec2(step));
}

} // namespace piMapper
} // namespace ofx

