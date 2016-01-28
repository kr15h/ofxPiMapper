#include "GridWarpSurface.h"

namespace ofx {
namespace piMapper {

GridWarpSurface::GridWarpSurface(){
	_gridCols = 2;
	_gridRows = 3;
	createGridMesh();
}

void GridWarpSurface::draw(){
	if(source->getTexture() == 0){
		return;
	}
	
	if(!source->getTexture()->isAllocated()){
		return;
	}
	
	source->getTexture()->bind();
	mesh.draw();
	source->getTexture()->unbind();
	
	// debug vertices
	mesh.drawWireframe();
	//mesh.drawVertices();
}

void GridWarpSurface::moveBy(ofVec2f v){
	/*
	vector <ofVec3f> & vertices = getVertices();
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v;
	}
	setMoved(true);
	*/
}

int GridWarpSurface::getType(){
	return SurfaceType::GRID_WARP_SURFACE;
}

bool GridWarpSurface::hitTest(ofVec2f p){
	ofPolyline pl;
	int vertsPerCol = _gridRows + 1;
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
			
			if(pl.inside(p)){
				return true;
			}
		}
	}
	
	return false;
}

ofPolyline GridWarpSurface::getHitArea(){
	ofPolyline pl;
	int vertsPerCol = _gridRows + 1;
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
	vector <ofVec2f> & texCoords = mesh.getTexCoords();
	ofVec2f textureSize = ofVec2f(source->getTexture()->getWidth(), source->getTexture()->getHeight());
	for(int i = 0; i < texCoords.size(); i++){
		line.addVertex(ofPoint(texCoords[i] * textureSize));
	}
	line.close();

	return line;
}

void GridWarpSurface::setVertex(int index, ofVec2f p){
	if(index >= mesh.getVertices().size()){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}
	mesh.setVertex(index, p);
}

void GridWarpSurface::setVertices(vector<ofVec2f> v){
	if(v.size() != mesh.getVertices().size()){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < v.size(); ++i){
		mesh.setVertex(i, v[i]);
	}
}

vector <ofVec3f> & GridWarpSurface::getVertices(){
	return mesh.getVertices();
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
			mesh.addVertex(
				ofVec2f(
					margin + (vertexDistanceX * (float)ix),
					margin + (vertexDistanceY * (float)iy) ));
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
			mesh.addTexCoord(ofVec2f(xc, yc));
		}
	}
}



} // namespace piMapper
} // namespace ofx