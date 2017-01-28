#include "AddSurfaceCmd.h"

namespace ofx {
namespace piMapper {

AddSurfaceCmd::AddSurfaceCmd(SurfaceManager * sm, SurfaceType surfaceType){
	_surfaceManager = sm;
	_surfaceType = surfaceType;
	_selectedSurface = 0;
}

void AddSurfaceCmd::exec(){
	_selectedSurface = _surfaceManager->getSelectedSurface();
	BaseSurface * surface = SurfaceFactory::instance()->createSurface(_surfaceType);
	_surfaceManager->addSurface(surface);
	_surfaceManager->selectSurface(surface);
}

void AddSurfaceCmd::undo(){
	ofLogNotice("AddSurfaceCmd", "undo");
	_surfaceManager->removeSurface();
	_surfaceManager->selectSurface(_selectedSurface);
}

} // namespace piMapper
} // namespace ofx

