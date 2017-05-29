#include "AddGridRowCmd.h"

namespace ofx {
namespace piMapper {

AddGridRowCmd::AddGridRowCmd(GridWarpSurface * s){
	_surface = s;
}

void AddGridRowCmd::exec(){

	// TODO: Figure out nice math to not loose existing vertex positions
	_vertices = _surface->getVertices();
	_texCoords = _surface->getTexCoords();
	_surface->setGridRows(_surface->getGridRows() + 1);
}

void AddGridRowCmd::undo(){
	ofLogNotice("AddGridRowCmd", "undo");
	_surface->setGridRows(_surface->getGridRows() - 1);
	vector <ofDefaultVec3> v;
	for(int i = 0; i < _vertices.size(); ++i){
		v.push_back(_vertices[i]);
	}
	_surface->setVertices(v);
	_surface->setTexCoords(_texCoords);
}

} // namespace piMapper
} // namespace ofx

