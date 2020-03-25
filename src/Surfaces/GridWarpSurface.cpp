#include "GridWarpSurface.h"

namespace ofx {
namespace piMapper {

GridWarpSurface::GridWarpSurface(){
	_gridCols = 2;
	_gridRows = 2;
	createGridMesh();
}

void GridWarpSurface::draw(){
	if(source->getTexture() == 0){
		return;
	}
	
	if(!source->getTexture()->isAllocated()){
		return;
	}
	
	bool normalizedTexCoords = ofGetUsingNormalizedTexCoords();
	ofEnableNormalizedTexCoords();

	source->getTexture()->bind();
	mesh.draw();
	source->getTexture()->unbind();
	
	if(!normalizedTexCoords){
		ofDisableNormalizedTexCoords();
	}
}

void GridWarpSurface::moveBy(Vec3 v){
	for(int i = 0; i < mesh.getVertices().size(); i++){
		mesh.getVertices()[i] += v.toOf();
	}
	
	setMoved(true);
	std::vector<Vec3> vertices = Vec3::fromOf(mesh.getVertices());
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

void GridWarpSurface::fullScreen(){

}

int GridWarpSurface::getType(){
	return SurfaceType::GRID_WARP_SURFACE;
}

int GridWarpSurface::getGridRows(){
	return _gridRows;
}

int GridWarpSurface::getGridCols(){
	return _gridCols;
}

int GridWarpSurface::setGridRows(int r){
	_gridRows = r;
	createGridMesh();
	return r;
}

int GridWarpSurface::setGridCols(int c){
	_gridCols = c;
	createGridMesh();
	return c;
}

bool GridWarpSurface::hitTest(Vec2 p){
	ofPolyline pl;
	int vertsPerRow = _gridCols + 1;
	
	for(int iy = 0; iy < _gridRows; ++iy){
		for(int ix = 0; ix < _gridCols; ++ix){
			int a = (iy * vertsPerRow) + ix;
			int b = (iy * vertsPerRow) + ix + 1;
			int c = ((iy + 1) * vertsPerRow) + ix + 1;
			int d = ((iy + 1) * vertsPerRow) + ix;
			
			pl.clear();
			pl.addVertex(mesh.getVertex(a));
			pl.addVertex(mesh.getVertex(b));
			pl.addVertex(mesh.getVertex(c));
			pl.addVertex(mesh.getVertex(d));
			pl.close();
			
			if(pl.inside(p.x, p.y)){
				return true;
			}
		}
	}
	
	return false;
}

ofPolyline GridWarpSurface::getHitArea(){
	ofPolyline pl;
	int vertsPerRow = _gridCols + 1;
	
	// Get the top border
	for(int ix = 0; ix <= _gridCols; ++ix){
		pl.addVertex(mesh.getVertex(ix));
	}
	
	// Get right border from top down
	for(int iy = 1; iy <= _gridRows; ++iy){
		int i = iy * vertsPerRow + vertsPerRow - 1;
		pl.addVertex(mesh.getVertex(i));
	}
	
	// Get bottom border from right to left
	for(int ix = _gridCols; ix >= 0; --ix){
		int i = _gridRows * vertsPerRow + vertsPerRow - 2;
		pl.addVertex(mesh.getVertex(i));
	}
	
	// Get left border from bottom to top
	for(int iy = _gridRows; iy > 0; --iy){
		int i = iy * vertsPerRow;
		pl.addVertex(mesh.getVertex(i));
	}
	
	pl.close();
	return pl;
}

ofPolyline GridWarpSurface::getTextureHitArea(){
	ofPolyline line;
	Vec2 textureSize = Vec2(source->getTexture()->getWidth(), source->getTexture()->getHeight());
	
	int vertsPerRow = _gridCols + 1;
	int vertsPerCol = _gridRows + 1;
	
	int a = 0;
	int b = _gridCols;
	int c = (_gridRows * vertsPerRow) + (vertsPerRow - 1);
	int d = (_gridRows * vertsPerRow);
	
	line.addVertex(ofPoint(mesh.getTexCoords()[a] * textureSize.toOf()));
	line.addVertex(ofPoint(mesh.getTexCoords()[b] * textureSize.toOf()));
	line.addVertex(ofPoint(mesh.getTexCoords()[c] * textureSize.toOf()));
	line.addVertex(ofPoint(mesh.getTexCoords()[d] * textureSize.toOf()));
	line.close();

	return line;
}

void GridWarpSurface::setVertex(int index, Vec3 vert){
	if(index >= mesh.getVertices().size()){
		throw runtime_error("Vertex with provided index does not exist");
	}
	
	mesh.setVertex(index, vert.toOf());
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void GridWarpSurface::setVertices(std::vector<Vec3> v){
	if(v.size() != mesh.getVertices().size()){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < v.size(); ++i){
		mesh.setVertex(i, v[i].toOf());
	}
	
	std::vector<Vec3> vertices = Vec3::fromOf(mesh.getVertices());
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

void GridWarpSurface::setTexCoord(int index, Vec2 t){
	if(index >= mesh.getVertices().size()){
		throw runtime_error("Texture coordinate with provided index does not exist");
	}
	mesh.setTexCoord(index, t.toOf());
}

void GridWarpSurface::setTexCoords(std::vector<Vec2> t){
	if(t.size() != mesh.getVertices().size()){
		throw runtime_error("Wrong number of texture coordinates");
	}
	for(int i = 0; i < t.size(); ++i){
		mesh.setTexCoord(i, t[i].toOf());
	}
}


std::vector<Vec3> GridWarpSurface::getVertices(){
	return Vec3::fromOf(mesh.getVertices());
}

std::vector<Vec2> GridWarpSurface::getTexCoords(){
	return Vec2::fromOf(mesh.getTexCoords());
}

void GridWarpSurface::createGridMesh(){
	mesh.clear();
	
	float margin = 100.0f;
	float surfaceWidth = (float)ofGetWidth() - margin * 2.0f;
	float surfaceHeight = (float)ofGetHeight() - margin * 2.0f;
	float vertexDistanceX = surfaceWidth / (float)_gridCols;
	float vertexDistanceY = surfaceHeight / (float)_gridRows;
	
	// Add vertices for each col and row
	for(int iy = 0; iy <= _gridRows; ++iy){
		for(int ix = 0; ix <= _gridCols; ++ix){
			mesh.addVertex(Vec3(
				margin + (vertexDistanceX * (float)ix),
				margin + (vertexDistanceY * (float)iy),
				0.0f).toOf());
		}
	}
	
	int vertsPerCol = _gridRows + 1;
	int vertsPerRow = _gridCols + 1;
	
	// Form triangles for all grid cols and rows
	for(int iy = 0; iy < _gridRows; ++iy){
		for(int ix = 0; ix < _gridCols; ++ix){
			int a = (iy * vertsPerRow) + ix;
			int b = (iy * vertsPerRow) + ix + 1;
			int c = ((iy + 1) * vertsPerRow) + ix + 1;
			int d = ((iy + 1) * vertsPerRow) + ix;
			mesh.addTriangle(a, b, c);
			mesh.addTriangle(a, c, d);
		}
	}
	
	// Add texture coordinates for each of the vertices
	for(int iy = 0; iy <= _gridRows; ++iy){
		for(int ix = 0; ix <= _gridCols; ++ix){
			float xc = (ix == 0) ? 0.0f : (float)ix / (float)_gridCols;
			float yc = (iy == 0) ? 0.0f : (float)iy / (float)_gridRows;
			mesh.addTexCoord(Vec2(xc, yc).toOf());
		}
	}
	
	std::vector<Vec3> vertices = Vec3::fromOf(mesh.getVertices());
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

BaseSurface * GridWarpSurface::clone(){
	GridWarpSurface * s = new GridWarpSurface();
	s->setVertices(getVertices());
	s->setTexCoords(getTexCoords());
    BaseSource * src = getSource();
    src->referenceCount++;
	s->setSource(src);
	return s;
}

} // namespace piMapper
} // namespace ofx
