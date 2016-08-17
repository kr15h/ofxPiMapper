#include "ScaleSurfaceUpCmd.h"

namespace ofx {
namespace piMapper {

ScaleSurfaceUpCmd::ScaleSurfaceUpCmd(BaseSurface * selectedSurface, float by){
	_selectedSurface = selectedSurface;
	_by = by;
}

void ScaleSurfaceUpCmd::exec(){
	ofLogNotice("ScaleSurfaceUpCmd", "exec");
	_selectedSurface->scaleTo(1.0f + _by);
}

void ScaleSurfaceUpCmd::undo(){
	ofLogNotice("ScaleSurfaceUpCmd", "undo");
	_selectedSurface->scaleTo(1.0f / (1.0f + _by));
}

} // namespace piMapper
} // namespace ofx

