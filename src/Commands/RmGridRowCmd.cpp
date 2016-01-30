#include "RmGridRowCmd.h"

namespace ofx {
namespace piMapper {

RmGridRowCmd::RmGridRowCmd(GridWarpSurface * s, ProjectionEditor * e){
	_surface = s;
	_editor = e;
	_doNotUndo = false;
}

void RmGridRowCmd::exec(){

	// TODO: Figure out nice math to not loose existing vertex positions
	
	if(_surface->getGridRows() > 1){
		_vertices = _surface->getVertices();
		_texCoords = _surface->getTexCoords();
		_surface->setGridRows(_surface->getGridRows() - 1);
		_editor->createJoints();
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
	vector <ofVec2f> v;
	
	for(int i = 0; i < _vertices.size(); ++i){
		v.push_back( ofVec2f(_vertices[i].x, _vertices[i].y) );
	}
	
	_surface->setVertices(v);
	_surface->setTexCoords(_texCoords);
	_editor->createJoints();
}

} // namespace piMapper
} // namespace ofx

