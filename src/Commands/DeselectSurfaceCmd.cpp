#include "DeselectSurfaceCmd.h"

namespace ofx {
namespace piMapper {

DeselectSurfaceCmd::DeselectSurfaceCmd(SurfaceManager * sm){
	_surfaceManager = sm;
	_surface = 0;
}

void DeselectSurfaceCmd::exec(){
	ofLogNotice("DeselectSurfaceCmd", "exec");
	_surface = _surfaceManager->getSelectedSurface();
	_selectedVertexIndex = _surfaceManager->getSelectedVertexIndex();
	_surfaceManager->deselectSurface();
}

void DeselectSurfaceCmd::undo(){
	ofLogNotice("DeselectSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_surface);
	_surfaceManager->selectVertex(_selectedVertexIndex);
}

} // namespace piMapper
} // namespace ofx

