#include "AddSurfaceCmd.h"

namespace ofx {
namespace piMapper {

AddSurfaceCmd::AddSurfaceCmd(SurfaceManager * sm, int surfaceType){
	_surfaceManager = sm;
	_surfaceType = surfaceType;
}

void AddSurfaceCmd::exec(){
	BaseSurface * surface = SurfaceFactory::instance()->createSurface(_surfaceType);
	_surfaceManager->addSurface(surface);
}

void AddSurfaceCmd::undo(){
	ofLogNotice("AddSurfaceCmd", "undo");
	_surfaceManager->removeSurface();
}

} // namespace piMapper
} // namespace ofx

