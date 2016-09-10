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
			calculateHomography();
		}
		
		ofRectangle box = getMeshBoundingBox();
		ofMesh m = mesh;
		
		m.setVertex(0, ofVec3f(0, 0, 0));
		m.setVertex(1, ofVec3f(box.width, 0, 0));
		m.setVertex(2, ofVec3f(box.width, box.height, 0));
		m.setVertex(3, ofVec3f(0, box.height, 0));
		
		ofPushMatrix();
		if(true){
			bool normalizedTexCoords = ofGetUsingNormalizedTexCoords();
			ofEnableNormalizedTexCoords();
			
			glMultMatrixf(_matrix);
			source->getTexture()->bind();
			m.draw();
			source->getTexture()->unbind();
			
			if(!normalizedTexCoords){
				ofDisableNormalizedTexCoords();
			}
		}
		ofPopMatrix();
	}else{
		bool normalizedTexCoords = ofGetUsingNormalizedTexCoords();
		ofEnableNormalizedTexCoords();
		
		ofPushStyle();
		ofSetColor(255, 255, 255);
	
		source->getTexture()->bind();
		mesh.draw();
		source->getTexture()->unbind();
		
		ofPopStyle();
		
		if(!normalizedTexCoords){
			ofDisableNormalizedTexCoords();
		}
	}
}

void QuadSurface::setVertex(int index, ofVec2f p){
	if(index > 3){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}

	mesh.setVertex(index, p);
	ofVec3f v = mesh.getVertex(index);
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void QuadSurface::setVertices(vector<ofVec2f> v){
	if(v.size() != 4){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < 4; ++i){
		mesh.setVertex(i, v[i]);
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void QuadSurface::setVertices(vector<ofVec3f> v){
	if(v.size() != 4){
		throw runtime_error("Wrong number of vertices");
	}
	
	for(int i = 0; i < 4; ++i){
		mesh.setVertex(i, v[i]);
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void QuadSurface::setTexCoord(int index, ofVec2f t){
	if(index > 3){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t);
}

void QuadSurface::setTexCoords(vector<ofVec2f> t){
	if(t.size() != 4){
		throw runtime_error("Wrong number of vertices");
	}
	for(int i = 0; i < 4; ++i){
		mesh.setTexCoord(i, t[i]);
	}
}

void QuadSurface::moveBy(ofVec2f v){
	vector <ofVec3f> & vertices = getVertices();
	
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += v;
	}
	
	setMoved(true);
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
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

void QuadSurface::calculateHomography(){
	float src[4][2];
    float dst[4][2];
	
	ofRectangle box = getMeshBoundingBox();
	
	src[0][0] = 0;
    src[0][1] = 0;
    src[1][0] = box.width;
    src[1][1] = 0;
    src[2][0] = box.width;
    src[2][1] = box.height;
    src[3][0] = 0;
    src[3][1] = box.height;
	
	ofVec3f p0 = mesh.getVertex(0);
	ofVec3f p1 = mesh.getVertex(1);
	ofVec3f p2 = mesh.getVertex(2);
	ofVec3f p3 = mesh.getVertex(3);

	dst[0][0] = p0.x;
	dst[0][1] = p0.y;
	dst[1][0] = p1.x;
	dst[1][1] = p1.y;
    dst[2][0] = p2.x;
	dst[2][1] = p2.y;
	dst[3][0] = p3.x;
	dst[3][1] = p3.y;
	
    HomographyHelper::findHomography(src, dst, _matrix);
}

void QuadSurface::setPerspectiveWarping(bool b){
	_perspectiveWarping = b;
}

bool QuadSurface::getPerspectiveWarping(){
	return _perspectiveWarping;
}

ofRectangle QuadSurface::getMeshBoundingBox(){
	float minX = 10000.0f;
	float minY = 10000.0f;
	float maxX = 0.0f;
	float maxY = 0.0f;
	
	for(int i = 0; i < mesh.getVertices().size(); ++i){
		if(mesh.getVertices()[i].x < minX){
			minX = mesh.getVertices()[i].x;
		}
		
		if(mesh.getVertices()[i].y < minY){
			minY = mesh.getVertices()[i].y;
		}
		
		if(mesh.getVertices()[i].x > maxX){
			maxX = mesh.getVertices()[i].x;
		}
		
		if(mesh.getVertices()[i].y > maxY){
			maxY = mesh.getVertices()[i].y;
		}
	}
	
	ofRectangle boundingBox = ofRectangle(ofPoint(minX, minY), ofPoint(maxX, maxY));
	return boundingBox;
}

BaseSurface * QuadSurface::clone(){
	QuadSurface * s = new QuadSurface();
	s->setVertices(getVertices());
	s->setTexCoords(getTexCoords());
	s->setPerspectiveWarping(getPerspectiveWarping());
    BaseSource * src = getSource();
    src->referenceCount++;
	s->setSource(src);
	return s;
}

} // namespace piMapper
} // namespace ofx