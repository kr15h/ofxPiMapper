#include "SelNextVertexCmd.h"

namespace ofx {
namespace piMapper {

SelNextVertexCmd::SelNextVertexCmd(BaseSurface * s){
	_surface = s;
}

void SelNextVertexCmd::exec(){

}

void SelNextVertexCmd::undo(){
	ofLogNotice("SelNextVertexCmd", "undo");
	
}

} // namespace piMapper
} // namespace ofx

