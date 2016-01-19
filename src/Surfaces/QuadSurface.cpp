#include "QuadSurface.h"

namespace ofx {
namespace piMapper {

QuadSurface::QuadSurface(){
	_perspectiveWarping = false;
	setup();
}

QuadSurface::~QuadSurface(){
	cout << "QuadSurface destructor." << endl;
}

void QuadSurface::setup(){
	// Create 4 points for the 2 triangles
	ofVec2f p1 = ofVec2f(0, 0);
	ofVec2f p2 = ofVec2f(0, ofGetHeight());
	ofVec2f p3 = ofVec2f(ofGetWidth(), ofGetHeight());
	ofVec2f p4 = ofVec2f(ofGetWidth(), 0);

	// Create 4 point for the texture coordinates
	ofVec2f t1 = ofVec2f(ofVec2f(0.0f, 0.0f));
	ofVec2f t2 = ofVec2f(ofVec2f(1.0f, 0.0f));
	ofVec2f t3 = ofVec2f(ofVec2f(1.0f, 1.0f));
	ofVec2f t4 = ofVec2f(ofVec2f(0.0f, 1.0f));

	setup(p1, p2, p3, p4, t1, t2, t3, t4, source);
}

void QuadSurface::setup(ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f p4,
						ofVec2f t1, ofVec2f t2, ofVec2f t3, ofVec2f t4,
						BaseSource * newSource){
	// Assign texture
	source = newSource;

	// Clear mesh
	mesh.clear();

	// Create a surface with the points
	mesh.addVertex(p1);
	mesh.addVertex(p2);
	mesh.addVertex(p3);
	mesh.addVertex(p4);

	// Add 2 triangles
	mesh.addTriangle(0, 2, 3);
	mesh.addTriangle(0, 1, 2);

	// Add texture coordinates
	mesh.addTexCoord(t1);
	mesh.addTexCoord(t2);
	mesh.addTexCoord(t3);
	mesh.addTexCoord(t4);

	// Pure GL setup
	// indices
	quadIndices[0] = 0;
	quadIndices[1] = 1;
	quadIndices[2] = 2;
	quadIndices[3] = 0;
	quadIndices[4] = 2;
	quadIndices[5] = 3;
	// tex coords (those are alway 0)
	quadTexCoordinates[2] = 0;
	quadTexCoordinates[6] = 0;
	quadTexCoordinates[10] = 0;
	quadTexCoordinates[14] = 0;

	calculate4dTextureCoords();
}

void QuadSurface::draw(){
	if(source->getTexture() == 0){
		return;
	}
	
	if(!source->getTexture()->isAllocated()){
		return;
	}

	if(_perspectiveWarping){
		if(mesh.haveVertsChanged() || mesh.haveTexCoordsChanged()){
			calculate4dTextureCoords();
		}
	
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(4, GL_FLOAT, 0, quadTexCoordinates);
		glVertexPointer(3, GL_FLOAT, 0, quadVertices);

		source->getTexture()->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, quadIndices);
		source->getTexture()->unbind();
	}else{
		source->getTexture()->bind();
		mesh.draw();
		source->getTexture()->unbind();
	}
}

void QuadSurface::setVertex(int index, ofVec2f p){
	if(index > 3){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}

	mesh.setVertex(index, p);
	calculate4dTextureCoords();
}

void QuadSurface::setVertices(vector<ofVec2f> v){
	if(v.size() != 4){
		throw runtime_error("Wrong number of vertices");
	}
	for(int i = 0; i < 4; ++i){
		mesh.setVertex(i, v[i]);
	}
	calculate4dTextureCoords();
}

void QuadSurface::setTexCoord(int index, ofVec2f t){
	if(index > 3){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t);
	calculate4dTextureCoords();
}

void QuadSurface::setTexCoords(vector<ofVec2f> t){
	if(t.size() != 4){
		throw runtime_error("Wrong number of vertices");
	}
	for(int i = 0; i < 4; ++i){
		mesh.setTexCoord(i, t[i]);
	}
	calculate4dTextureCoords();
}

void QuadSurface::moveBy(ofVec2f v){
	vector <ofVec3f> & vertices = getVertices();
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v;
	}
	calculate4dTextureCoords();
	setMoved(true);
}

int QuadSurface::getType(){
	return SurfaceType::QUAD_SURFACE;
}

bool QuadSurface::hitTest(ofVec2f p){
	// Construct ofPolyline from vertices
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

ofVec2f QuadSurface::getVertex(int index){
	if(index > 3){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		throw runtime_error("Vertex index out of bounds.");
	}

	ofVec3f vert = mesh.getVertex(index);
	return ofVec2f(vert.x, vert.y);
}

ofVec2f QuadSurface::getTexCoord(int index){
	if(index > 3){
		throw runtime_error("Texture coordinate index out of bounds.");
	}

	return mesh.getTexCoord(index);
}

ofPolyline QuadSurface::getHitArea(){
	ofPolyline line;
	line.addVertex(ofPoint(mesh.getVertex(0).x, mesh.getVertex(0).y));
	line.addVertex(ofPoint(mesh.getVertex(1).x, mesh.getVertex(1).y));
	line.addVertex(ofPoint(mesh.getVertex(2).x, mesh.getVertex(2).y));
	line.addVertex(ofPoint(mesh.getVertex(3).x, mesh.getVertex(3).y));
	line.close();

	return line;
}

ofPolyline QuadSurface::getTextureHitArea(){
	ofPolyline line;
	vector <ofVec2f> & texCoords = mesh.getTexCoords();
	ofVec2f textureSize = ofVec2f(source->getTexture()->getWidth(), source->getTexture()->getHeight());
	for(int i = 0; i < texCoords.size(); i++){
		line.addVertex(ofPoint(texCoords[i] * textureSize));
	}
	line.close();

	return line;
}

vector <ofVec3f> & QuadSurface::getVertices(){
	// return only joint vertices
	return mesh.getVertices();
}

vector <ofVec2f> & QuadSurface::getTexCoords(){
	return mesh.getTexCoords();
}

void QuadSurface::calculate4dTextureCoords(){
	// Perspective Warping with OpenGL Fixed Pipeline and q coordinates
	// see:
	// http://www.reedbeta.com/blog/2012/05/26/quadrilateral-interpolation-part-1/
	// for information on the technique
	// Pue OpenGL is used because the ofMesh sadly doesn't support ofVec4f as
	// texture coordinates.
	// calculate intersection point
	ofVec3f p0 = mesh.getVertex(0);
	ofVec3f p1 = mesh.getVertex(1);
	ofVec3f p2 = mesh.getVertex(2);
	ofVec3f p3 = mesh.getVertex(3);

	ofVec3f t0 = mesh.getTexCoord(0);
	ofVec3f t1 = mesh.getTexCoord(1);
	ofVec3f t2 = mesh.getTexCoord(2);
	ofVec3f t3 = mesh.getTexCoord(3);

	ofPoint interSect;
	ofLineSegmentIntersection(ofPoint(p0.x, p0.y), ofPoint(p2.x, p2.y),
							  ofPoint(p1.x, p1.y), ofPoint(p3.x, p3.y),
							  interSect);
	ofVec3f interSecVec = ofVec3f(interSect.x, interSect.y, 0);

	// calculate distances to intersection point
	float d0 = interSecVec.distance(p0);
	float d1 = interSecVec.distance(p1);
	float d2 = interSecVec.distance(p2);
	float d3 = interSecVec.distance(p3);

	// vertices
	// top left corner
	quadVertices[0] = p0.x;
	quadVertices[1] = p0.y;
	quadVertices[2] = 0;
	// top right corner
	quadVertices[3] = p1.x;
	quadVertices[4] = p1.y;
	quadVertices[5] = 0;
	// bottom right corner
	quadVertices[6] = p2.x;
	quadVertices[7] = p2.y;
	quadVertices[8] = 0;
	// bottom left corner
	quadVertices[9] = p3.x;
	quadVertices[10] = p3.y;
	quadVertices[11] = 0;

	float q0 = (d0 + d2) / (d2);
	float q1 = (d1 + d3) / (d3);
	float q2 = (d2 + d0) / (d0);
	float q3 = (d3 + d1) / (d1);

	quadTexCoordinates[0] = t0.x;
	quadTexCoordinates[1] = t0.y;
	quadTexCoordinates[3] = q0;

	quadTexCoordinates[4] = t1.x * q1;
	quadTexCoordinates[5] = t1.y;
	quadTexCoordinates[7] = q1;

	quadTexCoordinates[8] = t2.x * q2;
	quadTexCoordinates[9] = t2.y * q2;
	quadTexCoordinates[11] = q2;

	quadTexCoordinates[12] = t3.x;
	quadTexCoordinates[13] = t3.y * q3;
	quadTexCoordinates[15] = q3;
}

void QuadSurface::setPerspectiveWarping(bool b){
	_perspectiveWarping = b;
}

bool QuadSurface::getPerspectiveWarping(){
	return _perspectiveWarping;
}

} // namespace piMapper
} // namespace ofx