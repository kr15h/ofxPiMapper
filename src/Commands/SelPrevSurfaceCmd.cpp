#include "SelPrevSurfaceCmd.h"

namespace ofx {
namespace piMapper {

SelPrevSurfaceCmd::SelPrevSurfaceCmd(SurfaceManager * surfaceManager){
	_surfaceManager = surfaceManager;
}

void SelPrevSurfaceCmd::exec(){
	_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	_surfaceManager->selectPrevSurface();
	Gui::instance()->getScaleWidget().setSurface(_surfaceManager->getSelectedSurface());
}

void SelPrevSurfaceCmd::undo(){
	ofLogNotice("SelPrevSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_prevSelectedSurface);
	if(_prevSelectedSurface != 0){
		Gui::instance()->getScaleWidget().setSurface(_prevSelectedSurface);
	}
	_prevSelectedSurface = 0;
}

} // namespace piMapper
} // namespace ofx

