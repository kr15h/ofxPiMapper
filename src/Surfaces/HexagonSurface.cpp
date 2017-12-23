#include "HexagonSurface.h"

namespace ofx {
namespace piMapper {

HexagonSurface::HexagonSurface(){
	setup();
}

void HexagonSurface::setup(){

	// Create 6 + 1 points for the hexagon surface.
	
	vector <Vec2> verts;
	verts.resize(7);
	
	// Start with the center.
	verts[0] = Vec2((float)ofGetWidth() / 2.0f, (float)ofGetHeight() / 2.0f);
	
	// Then from top left clockwise.
	verts[1] = Vec2((float)ofGetWidth() / 3.0f, 0);
	verts[2] = Vec2((float)ofGetWidth() / 3.0f * 2.0f, 0);
	verts[3] = Vec2(ofGetWidth(), (float)ofGetHeight() / 2.0f);
	verts[4] = Vec2((float)ofGetWidth() / 3.0f * 2.0f, ofGetHeight());
	verts[5] = Vec2((float)ofGetWidth() / 3.0f, ofGetHeight());
	verts[6] = Vec2(0, (float)ofGetHeight() / 2.0f);
	
	// No create the texture coordinates.
	vector <Vec2> coords;
	coords.resize(7);
	
	// Start with center.
	coords[0] = Vec2(0.5f, 0.5f);
	
	// Then from top left and go clockwise.
	coords[1] = Vec2(1.0f / 3.0f, 0.0f);
	coords[2] = Vec2(1.0f / 3.0f * 2.0f, 0.0f);
	coords[3] = Vec2(1.0f, 0.5f);
	coords[4] = Vec2(1.0f / 3.0f * 2.0f, 1.0f);
	coords[5] = Vec2(1.0f / 3.0f, 1.0f);
	coords[6] = Vec2(0.0f, 0.5f);
	
	// And finally setup
	setup(verts, coords, source);
}

void HexagonSurface::setup(
	vector <Vec2> & verts,
	vector <Vec2> & coords,
	BaseSource * newSource){
	
	// Assign texture
	source = newSource;

	// Clear mesh
	mesh.clear();

	// Add vertices to the mesh
	for(unsigned int i = 0; i < verts.size(); ++i){
		mesh.addVertex(verts[i].toOf());
	}
	
	// Form triangles
	for(unsigned int i = 1; i < verts.size() - 1; ++i){
		unsigned int v1 = 0; // Center vertex always there
		unsigned int v2 = i;
		unsigned int v3 = i + 1;
		mesh.addTriangle(v1, v2, v3);
		
		// Add the last triangle
		if(i == verts.size() - 2){
			v1 = 0;
			v2 = i + 1;
			v3 = 1;
			mesh.addTriangle(v1, v2, v3);
		}
	}
	
	// Add texture coords
	for(unsigned int i = 0; i < coords.size(); ++i){
		mesh.addTexCoord(coords[i].toOf());
	}
}

void HexagonSurface::draw(){
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

void HexagonSurface::setVertex(int index, Vec2 p){
	if(index >= mesh.getVertices().size()){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}
	
	mesh.setVertex(index, p.toOf());
	ofVec3f v = mesh.getVertex(index);
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void HexagonSurface::setVertices(vector<Vec2> v){
	if(v.size() != mesh.getVertices().size()){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < v.size(); ++i){
		mesh.setVertex(i, v[i].toOf());
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void HexagonSurface::setVertices(vector<ofVec3f> v){
	if(v.size() != mesh.getVertices().size()){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < v.size(); ++i){
		mesh.setVertex(i, v[i]);
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void HexagonSurface::setTexCoord(int index, Vec2 t){
	if(index >= mesh.getTexCoords().size()){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t.toOf());
}

void HexagonSurface::setTexCoords(vector<Vec2> t){
	if(t.size() != mesh.getTexCoords().size()){
		throw runtime_error("Wrong number of texture coordinates");
	}
	for(int i = 0; i < t.size(); ++i){
		mesh.setTexCoord(i, t[i].toOf());
	}
}

void HexagonSurface::moveBy(Vec2 v){
	vector <ofVec3f> & vertices = getVertices();
	
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v.toOf();
	}
	
	setMoved(true);
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

int HexagonSurface::getType(){
	return SurfaceType::HEXAGON_SURFACE;
}

bool HexagonSurface::hitTest(Vec2 p){
	// Construct ofPolyline from vertices
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

Vec2 HexagonSurface::getVertex(int index){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		throw runtime_error("Vertex index out of bounds.");
	}

	ofVec3f vert = mesh.getVertex(index);
	return Vec2(vert.x, vert.y);
}

Vec2 HexagonSurface::getTexCoord(int index){
	if(index > 2){
		throw runtime_error("Texture coordinate index out of bounds.");
	}
	
	return Vec2(
		mesh.getTexCoord(index).x,
		mesh.getTexCoord(index).y);
}

ofPolyline HexagonSurface::getHitArea(){
	ofPolyline line;
	
	for(unsigned int i = 1; i < mesh.getVertices().size(); ++i){
		line.addVertex(ofPoint(mesh.getVertex(i).x, mesh.getVertex(i).y));
	}
	
	line.close();

	return line;
}

ofPolyline HexagonSurface::getTextureHitArea(){
	ofPolyline line;
	Vec2 textureSize = Vec2(
		source->getTexture()->getWidth(),
		source->getTexture()->getHeight());
	
	for(int i = 1; i < mesh.getTexCoords().size(); i++){
		line.addVertex(ofPoint(mesh.getTexCoords()[i] * textureSize.toOf()));
	}
	
	line.close();
	return line;
}

vector <ofVec3f> & HexagonSurface::getVertices(){
	// return only joint vertices
	return mesh.getVertices();
}

vector <Vec2> & HexagonSurface::getTexCoords(){
	_texCoords.clear();
	for(auto tc : mesh.getTexCoords()){
		_texCoords.push_back(tc);
	}
	return _texCoords;
}

BaseSurface * HexagonSurface::clone(){
	HexagonSurface * s = new HexagonSurface();
	s->setVertices(getVertices());
	s->setTexCoords(getTexCoords());
    BaseSource * src = getSource();
    src->referenceCount++;
	s->setSource(src);
	return s;
}

} // namespace piMapper
} // namespace ofx
