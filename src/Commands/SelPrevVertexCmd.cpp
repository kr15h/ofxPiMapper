#include "SelPrevVertexCmd.h"

namespace ofx {
namespace piMapper {

SelPrevVertexCmd::SelPrevVertexCmd(BaseSurface * s){
	_surface = s;
}

void SelPrevVertexCmd::exec(){

}

void SelPrevVertexCmd::undo(){
	ofLogNotice("SelPrevVertexCmd", "undo");
	
}

} // namespace piMapper
} // namespace ofx

