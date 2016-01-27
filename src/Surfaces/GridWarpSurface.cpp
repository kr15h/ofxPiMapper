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
}

void GridWarpSurface::moveBy(ofVec2f v){
	vector <ofVec3f> & vertices = getVertices();
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v;
	}
	setMoved(true);
}

int GridWarpSurface::getType(){
	return SurfaceType::GRID_WARP_SURFACE;
}

bool GridWarpSurface::hitTest(ofVec2f p){
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

ofPolyline GridWarpSurface::getHitArea(){
	ofPolyline line;
	line.addVertex(ofPoint(mesh.getVertex(0).x, mesh.getVertex(0).y));
	line.addVertex(ofPoint(mesh.getVertex(1).x, mesh.getVertex(1).y));
	line.addVertex(ofPoint(mesh.getVertex(2).x, mesh.getVertex(2).y));
	line.addVertex(ofPoint(mesh.getVertex(3).x, mesh.getVertex(3).y));
	line.close();

	return line;
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

void GridWarpSurface::createGridMesh(){
	// Assign texture
	source = getDefaultSource();

	// Clear mesh
	mesh.clear();
	
	float margin = 100.0f;
	float surfaceWidth = (float)ofGetWidth() - margin * 2.0f;
	float surfaceHeight = (float)ofGetHeight() - margin * 2.0f;
	float vertexDistanceX = surfaceWidth / (float)_gridCols;
	float vertexDistanceY = surfaceHeight / (float)_gridRows;
	
	// Add vertices for each col and row
	for(int ix = 0; ix <= _gridCols; ++ix){
		for(int iy = 0; iy <= _gridRows; ++iy){
			mesh.addVertex(
				ofVec2f(
					margin + vertexDistanceX * (float)ix,
					margin + vertexDistanceY * (float)iy));
		}
	}
	
	int vertsPerCol = _gridCols + 1;
	int vertsPerRow = _gridRows + 1;
	
	// Form triangles for all grid cols and rows
	for(int ix = 0; ix < _gridCols; ++ix){
		for(int iy = 0; iy < _gridRows; ++iy){
			
			mesh.addTriangle(
				(iy * vertsPerRow) + ix,
				((iy + 1) * vertsPerRow) + ix,
				((iy + 1) * vertsPerRow) + (ix + 1));
		
			mesh.addTriangle(
				(iy * vertsPerRow) + ix,
				(iy * vertsPerRow) + (ix + 1),
				((iy + 1) * vertsPerRow) + ix);
		}
	}
	
	// Add texture coordinates for each of the vertices
	for(int ix = 0; ix <= _gridCols; ++ix){
		for(int iy = 0; iy <= _gridRows; ++iy){
			float xc = (ix == 0) ? 0.0f : (float)ix / (float)_gridCols;
			float yc = (iy == 0) ? 0.0f : (float)iy / (float)_gridRows;
			mesh.addTexCoord(ofVec2f(xc, yc));
		}
	}
}



} // namespace piMapper
} // namespace ofx