#include "SetTexMapDrawModeCmd.h"

namespace ofx {
namespace piMapper {

SetTexMapDrawModeCmd::SetTexMapDrawModeCmd(TextureMappingState * s, int m){
	_state = s;
	_newMode = m;
}

void SetTexMapDrawModeCmd::exec(){
	ofLogNotice("SetTexMapDrawModeCmd", "undo");
	_oldMode = 0; // _state->getDrawMode();
	// _state->setDrawMode(_newMode);
}

void SetTexMapDrawModeCmd::undo(){
	ofLogNotice("SetTexMapDrawModeCmd", "undo");
	// _state->setDrawMode(_oldMode);
}

} // namespace piMapper
} // namespace ofx

