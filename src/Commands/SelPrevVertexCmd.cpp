#include "SelPrevVertexCmd.h"

namespace ofx {
namespace piMapper {

SelPrevVertexCmd::SelPrevVertexCmd(SurfaceManager * sm){
	_surfaceManager = sm;
}

void SelPrevVertexCmd::exec(){
	_surfaceManager->selectPrevVertex();
}

void SelPrevVertexCmd::undo(){
	ofLogNotice("SelPrevVertexCmd", "undo");
	_surfaceManager->selectNextVertex();
}

} // namespace piMapper
} // namespace ofx

