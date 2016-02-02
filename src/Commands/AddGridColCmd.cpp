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
	vector <ofVec2f> v;
	for(int i = 0; i < _vertices.size(); ++i){
		v.push_back( ofVec2f(_vertices[i].x, _vertices[i].y) );
	}
	_surface->setVertices(v);
	_surface->setTexCoords(_texCoords);
}

} // namespace piMapper
} // namespace ofx

