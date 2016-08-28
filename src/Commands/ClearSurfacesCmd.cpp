#include "ClearSurfacesCmd.h"

namespace ofx {
namespace piMapper {

ClearSurfacesCmd::ClearSurfacesCmd(){
	_surfaces = SurfaceStack::instance()->getSurfaces();
}

void ClearSurfacesCmd::exec(){
	SurfaceStack::instance()->clear();
}

void ClearSurfacesCmd::undo(){
	ofLogNotice("ClearSurfacesCmd", "undo");
	for(unsigned int i = 0; i < _surfaces.size(); ++i){
		SurfaceStack::instance()->push_back(_surfaces[i]);
	}
}

} // namespace piMapper
} // namespace ofx

