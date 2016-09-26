#include "SetApplicationStateCmd.h"

namespace ofx {
namespace piMapper {

SetApplicationStateCmd::SetApplicationStateCmd(Application * app,
											   ApplicationBaseState * st,
											   SurfaceManagerGui * gui,
											   int mode){

	_application = app;
	_prevApplicationState = 0;
	_applicationState = st;

	// TODO: To be removed
	_gui = gui;
	_prevGuiMode = -1;
	_mode = mode;
}

void SetApplicationStateCmd::exec(){
	_prevApplicationState = _application->getState();
	_application->setState(_applicationState);
	_applicationState->setTranslation(ofPoint(0, 0));
	_translation = _prevApplicationState->getTranslation();
	
	Gui::instance()->getTextureEditorWidget().setSurface(
		_application->getSurfaceManager()->getSelectedSurface());

	// TODO: To be removed.
	_prevGuiMode = _gui->getMode();
	_gui->setMode(_mode);
}

void SetApplicationStateCmd::undo(){
	ofLogNotice("SetApplicationStateCmd", "undo");
	_application->setState(_prevApplicationState);
	_application->getState()->setTranslation(_translation);

	// TODO: To be removed.
	_gui->setMode(_prevGuiMode);
}

} // namespace piMapper
} // namespace ofx

