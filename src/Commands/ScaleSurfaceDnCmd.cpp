#include "ScaleSurfaceDnCmd.h"

namespace ofx {
namespace piMapper {

ScaleSurfaceDnCmd::ScaleSurfaceDnCmd(BaseSurface * selectedSurface, float by){
	_selectedSurface = selectedSurface;
	_by = by;
}

void ScaleSurfaceDnCmd::exec(){
	ofLogNotice("ScaleSurfaceDnCmd", "exec");
	_selectedSurface->scaleTo(_selectedSurface->getScale() - _by);
}

void ScaleSurfaceDnCmd::undo(){
	ofLogNotice("ScaleSurfaceCmd", "undo");
	_selectedSurface->scaleTo(_selectedSurface->getScale() + _by);
}

} // namespace piMapper
} // namespace ofx

