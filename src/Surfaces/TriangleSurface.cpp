#include "TriangleSurface.h"

namespace ofx {
namespace piMapper {

TriangleSurface::TriangleSurface(){
	setup();
}

TriangleSurface::~TriangleSurface(){}

void TriangleSurface::setup(){
	// Create 3 points for the triangle
	Vec2 p1 = Vec2(ofGetWidth() / 2.0f, 0);
	Vec2 p2 = Vec2(Vec2(0, ofGetHeight()));
	Vec2 p3 = Vec2(ofGetWidth(), ofGetHeight());

	// Create 3 point for the texture coordinates
	Vec2 t1 = Vec2(0.5f, 0);
	Vec2 t2 = Vec2(0, 1.0f);
	Vec2 t3 = Vec2(1, 1.0f);

	setup(p1, p2, p3, t1, t2, t3, source);
}

void TriangleSurface::setup(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 t1,
							Vec2 t2, Vec2 t3, BaseSource * newSource){
	// Assign texture
	source = newSource;

	// Clear mesh
	mesh.clear();

	// Create a surface with the points
	mesh.addVertex(p1.toOf());
	mesh.addVertex(p2.toOf());
	mesh.addVertex(p3.toOf());

	// Add texture coordinates
	mesh.addTexCoord(t1.toOf());
	mesh.addTexCoord(t2.toOf());
	mesh.addTexCoord(t3.toOf());
}

void TriangleSurface::draw(){
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

void TriangleSurface::setVertex(int index, Vec2 p){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}
	
	mesh.setVertex(index, p.toOf());
	ofVec3f v = mesh.getVertex(index);
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void TriangleSurface::setVertices(vector<Vec2> v){
	if(v.size() != 3){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < 3; ++i){
		mesh.setVertex(i, v[i].toOf());
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void TriangleSurface::setVertices(vector<ofVec3f> v){
	if(v.size() != 3){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < 3; ++i){
		mesh.setVertex(i, v[i]);
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void TriangleSurface::setTexCoord(int index, Vec2 t){
	if(index > 2){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t.toOf());
}

void TriangleSurface::setTexCoords(vector<Vec2> t){
	if(t.size() != 3){
		throw runtime_error("Wrong number of texture coordinates");
	}
	for(int i = 0; i < 3; ++i){
		mesh.setTexCoord(i, t[i].toOf());
	}
}

void TriangleSurface::moveBy(Vec2 v){
	vector <ofVec3f> & vertices = getVertices();
	
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v.toOf();
	}
	
	setMoved(true);
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

int TriangleSurface::getType(){
	return SurfaceType::TRIANGLE_SURFACE;
}

bool TriangleSurface::hitTest(Vec2 p){
	// Construct ofPolyline from vertices
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

Vec2 TriangleSurface::getVertex(int index){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		throw runtime_error("Vertex index out of bounds.");
	}

	ofVec3f vert = mesh.getVertex(index);
	return Vec2(vert.x, vert.y);
}

Vec2 TriangleSurface::getTexCoord(int index){
	if(index > 2){
		throw runtime_error("Texture coordinate index out of bounds.");
	}

	return Vec2(
		mesh.getTexCoord(index).x,
		mesh.getTexCoord(index).y);
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
	Vec2 textureSize = Vec2(source->getTexture()->getWidth(), source->getTexture()->getHeight());
	for(int i = 0; i < mesh.getTexCoords().size(); i++){
		line.addVertex(ofPoint(mesh.getTexCoords()[i] * textureSize.toOf()));
	}
	line.close();

	return line;
}

vector <ofVec3f> & TriangleSurface::getVertices(){
	// return only joint vertices
	return mesh.getVertices();
}

vector <Vec2> & TriangleSurface::getTexCoords(){
	_texCoords.clear();
	for(auto tc : mesh.getTexCoords()){
		_texCoords.push_back(tc);
	}
	return _texCoords;
}

BaseSurface * TriangleSurface::clone(){
	TriangleSurface * s = new TriangleSurface();
	s->setVertices(getVertices());
	s->setTexCoords(getTexCoords());
    BaseSource * src = getSource();
    src->referenceCount++;
	s->setSource(src);
	return s;
}

} // namespace piMapper
} // namespace ofx
