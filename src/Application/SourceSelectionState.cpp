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

void SourceSelectionState::draw(Application * app){
	app->getGui()->draw();
	
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSurfaceHighlightWidget().draw();
}

} // namespace piMapper
} // namespace ofx