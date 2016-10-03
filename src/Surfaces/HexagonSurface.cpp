#include "HexagonSurface.h"

namespace ofx {
namespace piMapper {

HexagonSurface::HexagonSurface(){
	setup();
}

void HexagonSurface::setup(){

	// Create 6 + 1 points for the hexagon surface.
	
	vector <ofVec2f> verts;
	verts.resize(7);
	
	// Start with the center.
	verts[0] = ofVec2f((float)ofGetWidth() / 2.0f, (float)ofGetHeight() / 2.0f);
	
	// Then from top left clockwise.
	verts[1] = ofVec2f((float)ofGetWidth() / 3.0f, 0);
	verts[2] = ofVec2f((float)ofGetWidth() / 3.0f * 2.0f, 0);
	verts[3] = ofVec2f(ofGetWidth(), (float)ofGetHeight() / 2.0f);
	verts[4] = ofVec2f((float)ofGetWidth() / 3.0f * 2.0f, ofGetHeight());
	verts[5] = ofVec2f((float)ofGetWidth() / 3.0f, ofGetHeight());
	verts[6] = ofVec2f(0, (float)ofGetHeight() / 2.0f);
	
	// No create the texture coordinates.
	vector <ofVec2f> coords;
	coords.resize(7);
	
	// Start with center.
	coords[0] = ofVec2f(0.5f, 0.5f);
	
	// Then from top left and go clockwise.
	coords[1] = ofVec2f(1.0f / 3.0f, 0.0f);
	coords[2] = ofVec2f(1.0f / 3.0f * 2.0f, 0.0f);
	coords[3] = ofVec2f(1.0f, 0.5f);
	coords[4] = ofVec2f(1.0f / 3.0f * 2.0f, 1.0f);
	coords[5] = ofVec2f(1.0f / 3.0f, 1.0f);
	coords[6] = ofVec2f(0.0f, 0.5f);
	
	// And finally setup
	setup(verts, coords, source);
}

void HexagonSurface::setup(
	vector <ofVec2f> & verts,
	vector <ofVec2f> & coords,
	BaseSource * newSource){
	
	// Assign texture
	source = newSource;

	// Clear mesh
	mesh.clear();

	// Add vertices to the mesh
	for(unsigned int i = 0; i < verts.size(); ++i){
		mesh.addVertex(verts[i]);
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
		mesh.addTexCoord(coords[i]);
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

void HexagonSurface::setVertex(int index, ofVec2f p){
	if(index >= mesh.getVertices().size()){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}
	
	mesh.setVertex(index, p);
	ofVec3f v = mesh.getVertex(index);
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void HexagonSurface::setVertices(vector<ofVec2f> v){
	if(v.size() != mesh.getVertices().size()){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < v.size(); ++i){
		mesh.setVertex(i, v[i]);
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

void HexagonSurface::setTexCoord(int index, ofVec2f t){
	if(index >= mesh.getTexCoords().size()){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t);
}

void HexagonSurface::setTexCoords(vector<ofVec2f> t){
	if(t.size() != mesh.getTexCoords().size()){
		throw runtime_error("Wrong number of texture coordinates");
	}
	for(int i = 0; i < t.size(); ++i){
		mesh.setTexCoord(i, t[i]);
	}
}

void HexagonSurface::moveBy(ofVec2f v){
	vector <ofVec3f> & vertices = getVertices();
	
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v;
	}
	
	setMoved(true);
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

int HexagonSurface::getType(){
	return SurfaceType::HEXAGON_SURFACE;
}

bool HexagonSurface::hitTest(ofVec2f p){
	// Construct ofPolyline from vertices
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

ofVec2f HexagonSurface::getVertex(int index){
	if(index > 2){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		throw runtime_error("Vertex index out of bounds.");
	}

	ofVec3f vert = mesh.getVertex(index);
	return ofVec2f(vert.x, vert.y);
}

ofVec2f HexagonSurface::getTexCoord(int index){
	if(index > 2){
		throw runtime_error("Texture coordinate index out of bounds.");
	}

	return mesh.getTexCoord(index);
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
	vector <ofVec2f> & texCoords = mesh.getTexCoords();
	ofVec2f textureSize = ofVec2f(
		source->getTexture()->getWidth(),
		source->getTexture()->getHeight());
	
	for(int i = 1; i < texCoords.size(); i++){
		line.addVertex(ofPoint(texCoords[i] * textureSize));
	}
	
	line.close();

	return line;
}

vector <ofVec3f> & HexagonSurface::getVertices(){
	// return only joint vertices
	return mesh.getVertices();
}

vector <ofVec2f> & HexagonSurface::getTexCoords(){
	return mesh.getTexCoords();
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