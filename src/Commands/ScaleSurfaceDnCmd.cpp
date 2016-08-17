#include "ScaleSurfaceDnCmd.h"

namespace ofx {
namespace piMapper {

ScaleSurfaceDnCmd::ScaleSurfaceDnCmd(BaseSurface * selectedSurface, float by){
	_selectedSurface = selectedSurface;
	_by = by;
}

void ScaleSurfaceDnCmd::exec(){
	ofLogNotice("ScaleSurfaceDnCmd", "exec");
	_selectedSurface->scaleTo(1.0f - _by);
}

void ScaleSurfaceDnCmd::undo(){
	ofLogNotice("ScaleSurfaceCmd", "undo");
	_selectedSurface->scaleTo(1.0f / (1.0f - _by));
}

} // namespace piMapper
} // namespace ofx

