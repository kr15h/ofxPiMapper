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

BaseSurface * SurfaceFactory::createSurface(int type){
	if(type == SurfaceType::TRIANGLE_SURFACE){
		
		vector <ofVec2f> vertices;
		float margin = 50.0f;
		vertices.push_back(ofVec2f((float)ofGetWidth() / 2.0f, margin));
		vertices.push_back(ofVec2f((float)ofGetWidth() - margin, (float)ofGetHeight() - margin));
		vertices.push_back(ofVec2f(margin, (float)ofGetHeight() - margin));

		vector <ofVec2f> texCoords;
		texCoords.push_back(ofVec2f(0.5f, 0.0f));
		texCoords.push_back(ofVec2f(1.0f, 1.0f));
		texCoords.push_back(ofVec2f(0.0f, 1.0f));
		
		TriangleSurface * triangleSurface = new TriangleSurface();

		for(int i = 0; i < 3; i++){
			triangleSurface->setVertex(i, vertices[i]);
			triangleSurface->setTexCoord(i, texCoords[i]);
		}
		
		return triangleSurface;
		
	}else if(type == SurfaceType::QUAD_SURFACE){
		
		vector <ofVec2f> vertices;
		float margin = 50.0f;
		vertices.push_back(ofVec2f(margin, margin));
		vertices.push_back(ofVec2f((float)ofGetWidth() - margin, margin));
		vertices.push_back(ofVec2f((float)ofGetWidth() - margin, (float)ofGetHeight() - margin));
		vertices.push_back(ofVec2f(margin, (float)ofGetHeight() - margin));

		vector <ofVec2f> texCoords;
		texCoords.push_back(ofVec2f(ofVec2f(0.0f, 0.0f)));
		texCoords.push_back(ofVec2f(ofVec2f(1.0f, 0.0f)));
		texCoords.push_back(ofVec2f(ofVec2f(1.0f, 1.0f)));
		texCoords.push_back(ofVec2f(ofVec2f(0.0f, 1.0f)));
		
		QuadSurface * quadSurface = new QuadSurface();
		
		for(int i = 0; i < 4; i++){
			quadSurface->setVertex(i, vertices[i]);
			quadSurface->setTexCoord(i, texCoords[i]);
		}
		
		return quadSurface;
		
	}else{
		throw runtime_error("Undefined surface type");
	}
}

} // namespace piMapper
} // namespace ofx
