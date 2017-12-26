#include "RmGridColCmd.h"

namespace ofx {
namespace piMapper {

RmGridColCmd::RmGridColCmd(GridWarpSurface * s){
	_surface = s;
	_doNotUndo = false;
}

void RmGridColCmd::exec(){

	// TODO: Figure out nice math to not loose existing vertex positions
	
	if(_surface->getGridCols() > 1){
		_vertices = _surface->getVertices();
		_texCoords = _surface->getTexCoords();
		_surface->setGridCols(_surface->getGridCols() - 1);
	}else{
		_doNotUndo = true;
	}
	
}

void RmGridColCmd::undo(){
	ofLogNotice("RmGridColCmd", "undo");
	
	if(_doNotUndo){
		return;
	}
	
	_surface->setGridCols(_surface->getGridCols() + 1);
	_surface->setVertices(_vertices);
	_surface->setTexCoords(_texCoords);
}

} // namespace piMapper
} // namespace ofx

