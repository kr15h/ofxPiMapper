#include "SourceSelectionMode.h"

namespace ofx {
namespace piMapper {

SourceSelectionMode * SourceSelectionMode::_instance = 0;

SourceSelectionMode * SourceSelectionMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::SourceSelectionMode();
	}
	return _instance;
}

void SourceSelectionMode::setup(Application * app){
	Gui::instance()->getSourcesEditorWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSourcesEditorWidget().setMediaServer(app->getMediaServer());
	Gui::instance()->getSourcesEditorWidget().setCmdManager(app->getCmdManager());
	Gui::instance()->getSourcesEditorWidget().setup();
}

void SourceSelectionMode::draw(Application * app){
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