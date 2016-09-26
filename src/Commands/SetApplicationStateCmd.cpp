#include "SetApplicationStateCmd.h"

namespace ofx {
namespace piMapper {

SetApplicationStateCmd::SetApplicationStateCmd(Application * app,
											   ApplicationBaseState * st){

	_application = app;
	_prevApplicationState = 0;
	_applicationState = st;
}

void SetApplicationStateCmd::exec(){
	_prevApplicationState = _application->getState();
	_application->setState(_applicationState);
	_applicationState->setTranslation(ofPoint(0, 0));
	_translation = _prevApplicationState->getTranslation();
	
	Gui::instance()->getTextureEditorWidget().setSurface(
		_application->getSurfaceManager()->getSelectedSurface());
	
	if(_applicationState != PresentationState::instance()){
		ofShowCursor();
	}else{
		ofHideCursor();
	}
}

void SetApplicationStateCmd::undo(){
	ofLogNotice("SetApplicationStateCmd", "undo");
	_application->setState(_prevApplicationState);
	_application->getState()->setTranslation(_translation);
	
	Gui::instance()->getTextureEditorWidget().setSurface(
		_application->getSurfaceManager()->getSelectedSurface());
	
	if(_prevApplicationState != PresentationState::instance()){
		ofShowCursor();
	}else{
		ofHideCursor();
	}
}

} // namespace piMapper
} // namespace ofx

