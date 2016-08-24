#include "ScaleSurfaceFromToCmd.h"

namespace ofx {
namespace piMapper {

ScaleSurfaceFromToCmd::ScaleSurfaceFromToCmd(BaseSurface * selectedSurface, float from, float to){
	_selectedSurface = selectedSurface;
	_scaleFrom = from;
	_scaleTo = to;
}

void ScaleSurfaceFromToCmd::exec(){
	ofLogNotice("ScaleSurfaceFromToCmd", "exec");
	_selectedSurface->scaleTo(_scaleTo);
}

void ScaleSurfaceFromToCmd::undo(){
	ofLogNotice("ScaleSurfaceFromToCmd", "undo");
	_selectedSurface->scaleTo(_scaleFrom);
}

} // namespace piMapper
} // namespace ofx

