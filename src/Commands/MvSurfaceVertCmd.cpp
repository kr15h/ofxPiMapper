#include "MvSurfaceVertCmd.h"

namespace ofx {
namespace piMapper {

MvSurfaceVertCmd::MvSurfaceVertCmd(int vertIndex,
								   BaseSurface * surface,
								   ProjectionEditor * projectionEditor){

	_vertIndex = vertIndex;
	_surface = surface;
	_projectionEditor = projectionEditor;
}

void MvSurfaceVertCmd::exec(){
	ofLogNotice("MvSurfaceVertCommand", "exec");
	_prevVertPos = _surface->getVertices()[_vertIndex];
}

void MvSurfaceVertCmd::undo(){
	ofLogNotice("MvSurfaceVertCommand", "undo");
	_surface->setVertex(_vertIndex, _prevVertPos);
	_projectionEditor->updateJoints();
	_projectionEditor = 0;
	_surface = 0;
}

} // namespace piMapper
} // namespace ofx

