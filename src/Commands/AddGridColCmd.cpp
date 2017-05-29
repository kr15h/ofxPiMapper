#include "AddGridColCmd.h"

namespace ofx {
namespace piMapper {

AddGridColCmd::AddGridColCmd(GridWarpSurface * s){
	_surface = s;
}

void AddGridColCmd::exec(){

	// TODO: Figure out nice math to not loose existing vertex positions
	_vertices = _surface->getVertices();
	_texCoords = _surface->getTexCoords();
	_surface->setGridCols(_surface->getGridCols() + 1);
}

void AddGridColCmd::undo(){
	ofLogNotice("AddGridColCmd", "undo");
	_surface->setGridCols(_surface->getGridCols() - 1);
	vector <ofDefaultVec3> v;
	for(int i = 0; i < _vertices.size(); ++i){
		v.push_back(_vertices[i]);
	}
	_surface->setVertices(v);
	_surface->setTexCoords(_texCoords);
}

} // namespace piMapper
} // namespace ofx

