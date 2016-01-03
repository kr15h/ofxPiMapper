#include "AddSurfaceCmd.h"

namespace ofx {
namespace piMapper {

AddSurfaceCmd::AddSurfaceCmd(ofxPiMapper * app, int surfaceType){
	_app = app;
	_surfaceType = surfaceType;
}

void AddSurfaceCmd::exec(){
	if(_surfaceType == SurfaceType::TRIANGLE_SURFACE){
		addTriangleSurface();
	}else if(_surfaceType == SurfaceType::QUAD_SURFACE){
		addQuadSurface();
	}
}

void AddSurfaceCmd::undo(){
	ofLogNotice("AddSurfaceCmd", "undo");
	_app->getSurfaceManager()->removeSurface();
}

void AddSurfaceCmd::addTriangleSurface(){
	int surfaceType = ofx::piMapper::SurfaceType::TRIANGLE_SURFACE;

	vector <ofVec2f> vertices;
	float margin = 50.0f;
	vertices.push_back(ofVec2f((float)ofGetWidth() / 2.0f, margin));
	vertices.push_back(ofVec2f((float)ofGetWidth() - margin, (float)ofGetHeight() - margin));
	vertices.push_back(ofVec2f(margin, (float)ofGetHeight() - margin));

	vector <ofVec2f> texCoords;
	texCoords.push_back(ofVec2f(0.5f, 0.0f));
	texCoords.push_back(ofVec2f(1.0f, 1.0f));
	texCoords.push_back(ofVec2f(0.0f, 1.0f));
	_app->getSurfaceManager()->createSurface(surfaceType, vertices, texCoords);
}

void AddSurfaceCmd::addQuadSurface(){
	int surfaceType = ofx::piMapper::SurfaceType::QUAD_SURFACE;

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

	_app->getSurfaceManager()->createSurface(surfaceType, vertices, texCoords);
}

} // namespace piMapper
} // namespace ofx

