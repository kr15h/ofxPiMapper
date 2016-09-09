#include "PresentationState.h"

namespace ofx {
namespace piMapper {

PresentationState * PresentationState::_instance = 0;

PresentationState * PresentationState::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::PresentationState();
	}
	return _instance;
}

void PresentationState::draw(Application * app){
	app->getSurfaceManager()->draw();
	app->getGui()->draw();
}

void PresentationState::onMousePressed(Application * app, ofMouseEventArgs & args){
    app->getCmdManager()->exec(
        new ofx::piMapper::SetApplicationStateCmd(
            app, ProjectionMappingState::instance(),
            app->getGui(), GuiMode::PROJECTION_MAPPING));
}

} // namespace piMapper
} // namespace ofx