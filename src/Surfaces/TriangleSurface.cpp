#include "TriangleSurface.h"

namespace ofx {
namespace piMapper {

TriangleSurface::TriangleSurface(){
	setup();
}

void TriangleSurface::setup(){

	// Create 3 points for the triangle
	Vec3 p1 = Vec3((float)ofGetWidth() / 2.0f, 0.0f, 0.0f);
	Vec3 p2 = Vec3(0.0f, (float)ofGetHeight(), 0.0f);
	Vec3 p3 = Vec3((float)ofGetWidth(), (float)ofGetHeight(), 0.0f);

	// Create 3 point for the texture coordinates
	Vec2 t1 = Vec2(0.5f, 0.0f);
	Vec2 t2 = Vec2(0.0f, 1.0f);
	Vec2 t3 = Vec2(1.0f, 1.0f);

	setup(p1, p2, p3, t1, t2, t3, source);
}

void TriangleSurface::setup(Vec3 p1, Vec3 p2, Vec3 p3, Vec2 t1,
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

void TriangleSurface::setVertex(int index, Vec3 p){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << std::endl;
		return;
	}
	
	mesh.setVertex(index, p.toOf());
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void TriangleSurface::setVertices(std::vector<Vec3> v){
	if(v.size() != 3){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < 3; ++i){
		mesh.setVertex(i, v[i].toOf());
	}
	
	std::vector<Vec3> vertices = Vec3::fromOf(mesh.getVertices());
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

void TriangleSurface::setTexCoord(int index, Vec2 t){
	if(index > 2){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< std::endl;
		return;
	}

	mesh.setTexCoord(index, t.toOf());
}

void TriangleSurface::setTexCoords(std::vector<Vec2> t){
	if(t.size() != 3){
		throw runtime_error("Wrong number of texture coordinates");
	}
	
	for(int i = 0; i < 3; ++i){
		mesh.setTexCoord(i, t[i].toOf());
	}
}

void TriangleSurface::moveBy(Vec3 v){
	for(auto i = 0; i < mesh.getVertices().size(); ++i){
		mesh.getVertices()[i] += v.toOf();
	}
	
	setMoved(true);
	std::vector<Vec3> vertices = Vec3::fromOf(mesh.getVertices());
	ofNotifyEvent(verticesChangedEvent, vertices, this);
}

int TriangleSurface::getType(){
	return SurfaceType::TRIANGLE_SURFACE;
}

bool TriangleSurface::hitTest(Vec2 p){
	ofPolyline line = getHitArea();
	
	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

Vec2 TriangleSurface::getVertex(int index){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << std::endl;
		throw runtime_error("Vertex index out of bounds.");
	}

	return Vec2(
		mesh.getVertex(index).x,
		mesh.getVertex(index).y);
}

Vec2 TriangleSurface::getTexCoord(int index){
	if(index > 2){
		ofLog() << "Texture coordinate with this index does not exist: " << index << std::endl;
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
	
	Vec2 textureSize = Vec2(
		source->getTexture()->getWidth(),
		source->getTexture()->getHeight());
	
	for(int i = 0; i < mesh.getTexCoords().size(); i++){
		line.addVertex(ofPoint(mesh.getTexCoords()[i] * textureSize.toOf()));
	}
	
	line.close();
	return line;
}

std::vector<Vec3> TriangleSurface::getVertices(){
 	return Vec3::fromOf(mesh.getVertices());
}

std::vector<Vec2> TriangleSurface::getTexCoords(){
	return Vec2::fromOf(mesh.getTexCoords());
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
