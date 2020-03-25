#include "FullscreenSurfaceCmd.h"

namespace ofx {
namespace piMapper {

FullscreenSurfaceCmd::FullscreenSurfaceCmd(BaseSurface * surface){
	_surface = surface;
}

void FullscreenSurfaceCmd::exec(){
	ofLogNotice("FullscreenSurfaceCmd", "exec");
    _previousVertices = _surface->getVertices();
    _surface->fullScreen();
}

void FullscreenSurfaceCmd::undo(){
    ofLogNotice("FullscreenSurfaceCmd", "undo");
    for(int i = 0; i < _surface->getVertices().size(); i++){
        _surface->setVertex(i,_previousVertices[i]);
    }
}

} // namespace piMapper
} // namespace ofx

