#include "ToggleAnimatedSourceCmd.h"

namespace ofx {
namespace piMapper {

ToggleAnimatedSourceCmd::ToggleAnimatedSourceCmd(BaseSurface * surface){
    _surface = surface;
}

void ToggleAnimatedSourceCmd::exec(){
	ofLogNotice("ToggleAnimatedSourceCmd", "exec");
    _surface->getSource()->togglePause();
}

void ToggleAnimatedSourceCmd::undo(){
	ofLogNotice("ToggleAnimatedSourceCmd", "undo");
	_surface->getSource()->togglePause();
}

} // namespace piMapper
} // namespace ofx

