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
	Gui::instance()->getSourcesEditorWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSourcesEditorWidget().setMediaServer(app->getMediaServer());
	Gui::instance()->getSourcesEditorWidget().setCmdManager(app->getCmdManager());
	Gui::instance()->getSourcesEditorWidget().setup();
}

void SourceSelectionState::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	app->getSurfaceManager()->draw();
	ofPopStyle();
	
	Gui::instance()->getSourcesEditorWidget().draw();
	
	// TODO: Move the following line to setup()
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSurfaceHighlightWidget().draw();
}

} // namespace piMapper
} // namespace ofx