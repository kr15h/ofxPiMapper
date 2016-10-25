#include "SetPresetCmd.h"

namespace ofx {
namespace piMapper {

SetPresetCmd::SetPresetCmd(Application * app, unsigned int pi){
	_app = app;
	_newPresetIndex = pi;
}

void SetPresetCmd::exec(){
	ofLogNotice("SetPresetCmd", "exec");
	_prevPresetIndex = _app->getSurfaceManager()->getActivePresetIndex();
	_app->getSurfaceManager()->deselectSurface();
	_selectedSurfaceIndex = _app->getSurfaceManager()->getSelectedSurfaceIndex();
	_app->getSurfaceManager()->setPreset(_newPresetIndex);
}

void SetPresetCmd::undo(){
	ofLogNotice("SetPresetCmd", "undo");
	_app->getSurfaceManager()->setPreset(_prevPresetIndex);
	_app->getSurfaceManager()->selectSurface(_selectedSurfaceIndex);
}

} // namespace piMapper
} // namespace ofx

