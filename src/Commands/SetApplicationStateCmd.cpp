#include "SetApplicationStateCmd.h"

namespace ofx {
namespace piMapper {

SetApplicationStateCmd::SetApplicationStateCmd(Application * app,
											   ApplicationBaseMode * st){

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
	
	if(_applicationState != PresentationMode::instance()){
		ofShowCursor();
	}else{
		ofHideCursor();
	}
	
	if(_applicationState == SourceSelectionMode::instance()){
		Gui::instance()->getSourcesEditorWidget().enable();
	}else{
		Gui::instance()->getSourcesEditorWidget().disable();
	}
}

void SetApplicationStateCmd::undo(){
	ofLogNotice("SetApplicationStateCmd", "undo");
	_application->setState(_prevApplicationState);
	_application->getState()->setTranslation(_translation);
	
	Gui::instance()->getTextureEditorWidget().setSurface(
		_application->getSurfaceManager()->getSelectedSurface());
	
	if(_prevApplicationState != PresentationMode::instance()){
		ofShowCursor();
	}else{
		ofHideCursor();
	}
	
	if(_prevApplicationState == SourceSelectionMode::instance()){
		Gui::instance()->getSourcesEditorWidget().enable();
	}else{
		Gui::instance()->getSourcesEditorWidget().disable();
	}
}

} // namespace piMapper
} // namespace ofx

