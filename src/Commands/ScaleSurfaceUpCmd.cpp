#include "ScaleSurfaceUpCmd.h"

namespace ofx {
namespace piMapper {

ScaleSurfaceUpCmd::ScaleSurfaceUpCmd(BaseSurface * selectedSurface, float by){
	_selectedSurface = selectedSurface;
	_by = by;
}

void ScaleSurfaceUpCmd::exec(){
	ofLogNotice("ScaleSurfaceUpCmd", "exec");
	_selectedSurface->scaleTo(_selectedSurface->getScale() + _by);
}

void ScaleSurfaceUpCmd::undo(){
	ofLogNotice("ScaleSurfaceUpCmd", "undo");
	_selectedSurface->scaleTo(_selectedSurface->getScale() - _by);
}

} // namespace piMapper
} // namespace ofx

