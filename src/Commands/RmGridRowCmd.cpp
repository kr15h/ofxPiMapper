#include "RmGridRowCmd.h"

namespace ofx {
namespace piMapper {

RmGridRowCmd::RmGridRowCmd(GridWarpSurface * s){
	_surface = s;
	_doNotUndo = false;
}

void RmGridRowCmd::exec(){

	// TODO: Figure out nice math to not loose existing vertex positions
	
	if(_surface->getGridRows() > 1){
		_vertices = _surface->getVertices();
		_texCoords = _surface->getTexCoords();
		_surface->setGridRows(_surface->getGridRows() - 1);
	}else{
		_doNotUndo = true;
	}
	
}

void RmGridRowCmd::undo(){
	ofLogNotice("RmGridRowCmd", "undo");
	
	if(_doNotUndo){
		return;
	}
	
	_surface->setGridRows(_surface->getGridRows() + 1);
	vector <ofDefaultVec3> v;
	
	for(int i = 0; i < _vertices.size(); ++i){
		v.push_back( _vertices[i] );
	}
	
	_surface->setVertices(v);
	_surface->setTexCoords(_texCoords);
}

} // namespace piMapper
} // namespace ofx

