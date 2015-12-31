#include "TriangleSurface.h"

namespace ofx {
namespace piMapper {

TriangleSurface::TriangleSurface(){
	setup();
}

TriangleSurface::~TriangleSurface(){}

void TriangleSurface::setup(){
	// Create 3 points for the triangle
	ofVec2f p1 = ofVec2f(ofGetWidth() / 2.0f, 0);
	ofVec2f p2 = ofVec2f(ofVec2f(0, ofGetHeight()));
	ofVec2f p3 = ofVec2f(ofGetWidth(), ofGetHeight());

	// Create 3 point for the texture coordinates
	ofVec2f t1 = ofVec2f(0.5f, 0);
	ofVec2f t2 = ofVec2f(0, 1.0f);
	ofVec2f t3 = ofVec2f(1, 1.0f);

	setup(p1, p2, p3, t1, t2, t3, source);
}

void TriangleSurface::setup(ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f t1,
							ofVec2f t2, ofVec2f t3, BaseSource * newSource){
	// Assign texture
	source = newSource;

	// Clear mesh
	mesh.clear();

	// Create a surface with the points
	mesh.addVertex(p1);
	mesh.addVertex(p2);
	mesh.addVertex(p3);

	// Add texture coordinates
	mesh.addTexCoord(t1);
	mesh.addTexCoord(t2);
	mesh.addTexCoord(t3);
}

void TriangleSurface::draw(){
	if(source->getTexture() == 0){
		ofLogWarning("TriangleSurface") << "Source texture is empty. Not drawing.";
		return;
	}

	source->getTexture()->bind();
	mesh.draw();
	source->getTexture()->unbind();
}

void TriangleSurface::setVertex(int index, ofVec2f p){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}

	mesh.setVertex(index, p);
}

void TriangleSurface::setTexCoord(int index, ofVec2f t){
	if(index > 2){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t);
}

void TriangleSurface::moveBy(ofVec2f v){
	vector <ofVec3f> & vertices = getVertices();
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v;
	}
	setMoved(true);
}

int TriangleSurface::getType(){
	return SurfaceType::TRIANGLE_SURFACE;
}

bool TriangleSurface::hitTest(ofVec2f p){
	// Construct ofPolyline from vertices
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

ofVec2f TriangleSurface::getVertex(int index){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		throw std::runtime_error("Vertex index out of bounds.");
	}

	ofVec3f vert = mesh.getVertex(index);
	return ofVec2f(vert.x, vert.y);
}

ofVec2f TriangleSurface::getTexCoord(int index){
	if(index > 2){
		throw std::runtime_error("Texture coordinate index out of bounds.");
	}

	return mesh.getTexCoord(index);
}

ofPolyline TriangleSurface::getHitArea(){
	ofPolyline line;
	line.addVertex(ofPoint(mesh.getVertex(0).x, mesh.getVertex(0).y));
	line.addVertex(ofPoint(mesh.getVertex(1).x, mesh.getVertex(1).y));
	line.addVertex(ofPoint(mesh.getVertex(2).x, mesh.getVertex(2).y));
	line.close();

	return line;
}

ofPolyline TriangleSurface::getTextureHitArea(){
	ofPolyline line;
	vector <ofVec2f> & texCoords = mesh.getTexCoords();
	ofVec2f textureSize = ofVec2f(source->getTexture()->getWidth(), source->getTexture()->getHeight());
	for(int i = 0; i < texCoords.size(); i++){
		line.addVertex(ofPoint(texCoords[i] * textureSize));
	}
	line.close();

	return line;
}

vector <ofVec3f> & TriangleSurface::getVertices(){
	// return only joint vertices
	return mesh.getVertices();
}

vector <ofVec2f> & TriangleSurface::getTexCoords(){
	return mesh.getTexCoords();
}

} // namespace piMapper
} // namespace ofx