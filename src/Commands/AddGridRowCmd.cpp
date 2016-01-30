#include "AddGridRowCmd.h"

namespace ofx {
namespace piMapper {

AddGridRowCmd::AddGridRowCmd(GridWarpSurface * s, ProjectionEditor * e){
	_surface = s;
	_editor = e;
}

void AddGridRowCmd::exec(){
	_vertices = _surface->getVertices();
	_texCoords = _surface->getTexCoords();
	_surface->setGridRows(_surface->getGridRows() + 1);
	_editor->createJoints();
}

void AddGridRowCmd::undo(){
	ofLogNotice("AddGridRowCmd", "undo");
	_surface->setGridRows(_surface->getGridRows() - 1);
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

