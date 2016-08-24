#include "SelNextSurfaceCmd.h"

namespace ofx {
namespace piMapper {

SelNextSurfaceCmd::SelNextSurfaceCmd(SurfaceManager * surfaceManager){
	_surfaceManager = surfaceManager;
}

void SelNextSurfaceCmd::exec(){
	_prevSelectedSurface = _surfaceManager->getSelectedSurface();
	_surfaceManager->selectNextSurface();
	Gui::instance()->getScaleWidget().setSurface(_surfaceManager->getSelectedSurface());
}

void SelNextSurfaceCmd::undo(){
	ofLogNotice("SelNextSurfaceCmd", "undo");
	_surfaceManager->selectSurface(_prevSelectedSurface);
	if(_prevSelectedSurface != 0){
		Gui::instance()->getScaleWidget().setSurface(_prevSelectedSurface);
	}
	_prevSelectedSurface = 0;
}

} // namespace piMapper
} // namespace ofx

