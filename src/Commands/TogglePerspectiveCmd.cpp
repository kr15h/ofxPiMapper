#include "TogglePerspectiveCmd.h"

namespace ofx {
namespace piMapper {

TogglePerspectiveCmd::TogglePerspectiveCmd(QuadSurface * surface){
	_surface = surface;
}

void TogglePerspectiveCmd::exec(){
	ofLogNotice("TogglePerspectiveCmd", "exec");
	_perspectiveBeforeExec = _surface->getPerspectiveWarping();
	_surface->setPerspectiveWarping(!_perspectiveBeforeExec);
}

void TogglePerspectiveCmd::undo(){
	ofLogNotice("TogglePerspectiveCmd", "undo");
	_surface->setPerspectiveWarping(_perspectiveBeforeExec);
	_surface = 0;
}

} // namespace piMapper
} // namespace ofx

