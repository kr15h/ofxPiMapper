#include "MvSurfaceVertCmd.h"

namespace ofx {
namespace piMapper {

MvSurfaceVertCmd::MvSurfaceVertCmd(int vertIndex, BaseSurface * surface){
	_vertIndex = vertIndex;
	_surface = surface;
}

void MvSurfaceVertCmd::exec(){
	ofLogNotice("MvSurfaceVertCommand", "exec");
	_prevVertPos = _surface->getVertices()[_vertIndex];
}

void MvSurfaceVertCmd::undo(){
	ofLogNotice("MvSurfaceVertCommand", "undo");
	_surface->setVertex(_vertIndex, _prevVertPos);
}

} // namespace piMapper
} // namespace ofx

