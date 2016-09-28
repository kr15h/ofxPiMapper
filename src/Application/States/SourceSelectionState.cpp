#include "SourceSelectionState.h"

namespace ofx {
namespace piMapper {

SourceSelectionState * SourceSelectionState::_instance = 0;

SourceSelectionState * SourceSelectionState::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::SourceSelectionState();
	}
	return _instance;
}

void SourceSelectionState::setup(Application * app){
	app->getGui()->getSourcesEditorWidget()->setSurfaceManager(app->getSurfaceManager());
	app->getGui()->getSourcesEditorWidget()->setup();
}

void SourceSelectionState::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	app->getSurfaceManager()->draw();
	ofPopStyle();
	
	// TODO: Separate SourcesEditorWidget from SurfaceManagerGui, make it a widget
	app->getGui()->getSourcesEditorWidget()->draw();
	
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSurfaceHighlightWidget().draw();
}

} // namespace piMapper
} // namespace ofx