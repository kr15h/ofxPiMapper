#include "AddSurfaceCmd.h"

namespace ofx {
namespace piMapper {

AddSurfaceCmd::AddSurfaceCmd(ofxPiMapper * app, int surfaceType){
	_app = app;
	_surfaceType = surfaceType;
}

void AddSurfaceCmd::exec(){
	BaseSurface * surface = SurfaceFactory::instance()->createSurface(_surfaceType);
	_app->getSurfaceManager()->addSurface(surface);
}

void AddSurfaceCmd::undo(){
	ofLogNotice("AddSurfaceCmd", "undo");
	_app->getSurfaceManager()->removeSurface();
}

} // namespace piMapper
} // namespace ofx

