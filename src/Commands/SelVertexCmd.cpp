#include "SelVertexCmd.h"

namespace ofx {
namespace piMapper {

SelVertexCmd::SelVertexCmd(SurfaceManager * sm, int i){
	_surfaceManager = sm;
	_newVertexIndex = i;
}

void SelVertexCmd::exec(){
	_prevVertexIndex = _surfaceManager->getSelectedVertexIndex();
	_surfaceManager->selectVertex(_newVertexIndex);
}

void SelVertexCmd::undo(){
	ofLogNotice("SelVertexCmd", "undo");
	_surfaceManager->selectVertex(_prevVertexIndex);
}

} // namespace piMapper
} // namespace ofx

