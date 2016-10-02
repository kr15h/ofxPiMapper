#include "ClearSurfacesCmd.h"

namespace ofx {
namespace piMapper {

ClearSurfacesCmd::ClearSurfacesCmd(SurfaceManager * sm){
	_surfaceManager = sm;
	_selectedSurface = _surfaceManager->getSelectedSurface();
	_surfaces = sm->getActivePreset()->getSurfaces();
}

void ClearSurfacesCmd::exec(){
	_surfaceManager->deselectSurface();
	_surfaceManager->getActivePreset()->clear();
}

void ClearSurfacesCmd::undo(){
	ofLogNotice("ClearSurfacesCmd", "undo");
	for(unsigned int i = 0; i < _surfaces.size(); ++i){
		_surfaceManager->getActivePreset()->push_back(_surfaces[i]);
	}
	_surfaceManager->selectSurface(_selectedSurface);
}

} // namespace piMapper
} // namespace ofx

