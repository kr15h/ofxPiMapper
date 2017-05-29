#include "SurfaceFactory.h"

namespace ofx {
namespace piMapper {

SurfaceFactory * SurfaceFactory::_instance = 0;

SurfaceFactory * SurfaceFactory::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::SurfaceFactory();
	}
	return _instance;
}

BaseSurface * SurfaceFactory::createSurface(SurfaceType type){
	if(type == SurfaceType::TRIANGLE_SURFACE){
		return createTriangleSurface();
	}else if(type == SurfaceType::QUAD_SURFACE){
		return createQuadSurface();
	}else if(type == SurfaceType::GRID_WARP_SURFACE){
		return createGridWarpSurface();
	}else if(type == SurfaceType::HEXAGON_SURFACE){
		return createHexagonSurface();
	}else{
		throw runtime_error("Undefined surface type");
	}
}

TriangleSurface * SurfaceFactory::createTriangleSurface(){
	vector <ofDefaultVec3> vertices;
	float margin = 50.0f;
	vertices.push_back(ofDefaultVec3((float)ofGetWidth() / 2.0f, margin, 0));
	vertices.push_back(ofDefaultVec3((float)ofGetWidth() - margin, (float)ofGetHeight() - margin, 0));
	vertices.push_back(ofDefaultVec3(margin, (float)ofGetHeight() - margin, 0));

	vector <ofDefaultVec2> texCoords;
	texCoords.push_back(ofDefaultVec2(0.5f, 0.0f));
	texCoords.push_back(ofDefaultVec2(1.0f, 1.0f));
	texCoords.push_back(ofDefaultVec2(0.0f, 1.0f));
	
	TriangleSurface * triangleSurface = new TriangleSurface();

	for(int i = 0; i < 3; i++){
		triangleSurface->setVertex(i, vertices[i]);
		triangleSurface->setTexCoord(i, texCoords[i]);
	}
	
	return triangleSurface;
}

QuadSurface * SurfaceFactory::createQuadSurface(){
	vector <ofDefaultVec3> vertices;
	float margin = 50.0f;
	vertices.push_back(ofDefaultVec3(margin, margin, 0));
	vertices.push_back(ofDefaultVec3((float)ofGetWidth() - margin, margin, 0));
	vertices.push_back(ofDefaultVec3((float)ofGetWidth() - margin, (float)ofGetHeight() - margin, 0));
	vertices.push_back(ofDefaultVec3(margin, (float)ofGetHeight() - margin, 0));

	vector <ofDefaultVec2> texCoords;
	texCoords.push_back(ofDefaultVec2(ofDefaultVec2(0.0f, 0.0f)));
	texCoords.push_back(ofDefaultVec2(ofDefaultVec2(1.0f, 0.0f)));
	texCoords.push_back(ofDefaultVec2(ofDefaultVec2(1.0f, 1.0f)));
	texCoords.push_back(ofDefaultVec2(ofDefaultVec2(0.0f, 1.0f)));
	
	QuadSurface * quadSurface = new QuadSurface();
	quadSurface->setPerspectiveWarping(true);
	
	for(int i = 0; i < 4; i++){
		quadSurface->setVertex(i, vertices[i]);
		quadSurface->setTexCoord(i, texCoords[i]);
	}
	
	return quadSurface;
}

GridWarpSurface * SurfaceFactory::createGridWarpSurface(){
	GridWarpSurface * gridWarpSurface = new GridWarpSurface();
	return gridWarpSurface;
}

HexagonSurface * SurfaceFactory::createHexagonSurface(){
	HexagonSurface * hexagonSurface = new HexagonSurface();
	return hexagonSurface;
}

} // namespace piMapper
} // namespace ofx
