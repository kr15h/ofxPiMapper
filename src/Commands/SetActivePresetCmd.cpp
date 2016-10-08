#include "SetActivePresetCmd.h"

namespace ofx {
namespace piMapper {

SetActivePresetCmd::SetActivePresetCmd(Application * app, unsigned int pi){
	_app = app;
	_newPresetIndex = pi;
}

void SetActivePresetCmd::exec(){
	ofLogNotice("SetActivePresetCmd", "exec");
	_prevPresetIndex = _app->getSurfaceManager()->getActivePresetIndex();
	_app->getSurfaceManager()->deselectSurface();
	_selectedSurfaceIndex = _app->getSurfaceManager()->getSelectedSurfaceIndex();
	_app->getSurfaceManager()->setActivePreset(_newPresetIndex);
}

void SetActivePresetCmd::undo(){
	ofLogNotice("SetActivePresetCmd", "undo");
	_app->getSurfaceManager()->setActivePreset(_prevPresetIndex);
	_app->getSurfaceManager()->selectSurface(_selectedSurfaceIndex);
}

} // namespace piMapper
} // namespace ofx

