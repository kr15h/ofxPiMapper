#include "SelNextVertexCmd.h"

namespace ofx {
namespace piMapper {

SelNextVertexCmd::SelNextVertexCmd(SurfaceManager * sm){
	_surfaceManager = sm;
}

void SelNextVertexCmd::exec(){
	_surfaceManager->selectNextVertex();
}

void SelNextVertexCmd::undo(){
	ofLogNotice("SelNextVertexCmd", "undo");
	_surfaceManager->selectPrevVertex();
}

} // namespace piMapper
} // namespace ofx

