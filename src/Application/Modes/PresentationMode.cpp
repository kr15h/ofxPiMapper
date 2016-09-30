#include "PresentationMode.h"

namespace ofx {
namespace piMapper {

PresentationMode * PresentationMode::_instance = 0;

PresentationMode * PresentationMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::PresentationMode();
	}
	return _instance;
}

void PresentationMode::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	app->getSurfaceManager()->draw();
	ofPopStyle();
}

void PresentationMode::onMousePressed(Application * app, ofMouseEventArgs & args){
    app->getCmdManager()->exec(
        new ofx::piMapper::SetApplicationModeCmd(
            app, ProjectionMappingMode::instance()));
}

} // namespace piMapper
} // namespace ofx