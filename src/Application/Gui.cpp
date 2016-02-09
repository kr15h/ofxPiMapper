#include "Gui.h"

namespace ofx {
namespace piMapper {

Gui * Gui::_instance = 0;

Gui * Gui::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::Gui();
	}
	return _instance;
}

void Gui::notifyEvent(ofMouseEventArgs & args){
	GuiEvent e;
	e.args = args;
	e.type = 1;
	ofNotifyEvent(event, e, this);
}

} // piMapper
} // ofx