#include "QuadSurface.h"

namespace ofx {
namespace piMapper {

QuadSurface::QuadSurface(){
	_perspectiveWarping = false;
	setup();
}

void QuadSurface::setup(){
	// Create 4 points for the 2 triangles
	ofDefaultVec3 v1 = ofDefaultVec3(0, 0, 0);
	ofDefaultVec3 v2 = ofDefaultVec3(0, ofGetHeight(), 0);
	ofDefaultVec3 v3 = ofDefaultVec3(ofGetWidth(), ofGetHeight(), 0);
	ofDefaultVec3 v4 = ofDefaultVec3(ofGetWidth(), 0, 0);

	// Create 4 point for the texture coordinates
	ofDefaultVec2 t1 = ofDefaultVec2(ofDefaultVec2(0.0f, 0.0f));
	ofDefaultVec2 t2 = ofDefaultVec2(ofDefaultVec2(1.0f, 0.0f));
	ofDefaultVec2 t3 = ofDefaultVec2(ofDefaultVec2(1.0f, 1.0f));
	ofDefaultVec2 t4 = ofDefaultVec2(ofDefaultVec2(0.0f, 1.0f));

	setup(v1, v2, v3, v4, t1, t2, t3, t4, source);
}

void QuadSurface::setup(
	ofDefaultVec3 v1,
	ofDefaultVec3 v2,
	ofDefaultVec3 v3,
	ofDefaultVec3 v4,
	ofDefaultVec2 t1,
	ofDefaultVec2 t2,
	ofDefaultVec2 t3,
	ofDefaultVec2 t4,
	BaseSource * newSource){
	
	// Assign texture
	source = newSource;

	// Clear mesh
	mesh.clear();

	// Create a surface with the points
	mesh.addVertex(v1);
	mesh.addVertex(v2);
	mesh.addVertex(v3);
	mesh.addVertex(v4);

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
		
		m.setVertex(0, ofDefaultVec3(0, 0, 0));
		m.setVertex(1, ofDefaultVec3(box.width, 0, 0));
		m.setVertex(2, ofDefaultVec3(box.width, box.height, 0));
		m.setVertex(3, ofDefaultVec3(0, box.height, 0));
		
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

void QuadSurface::setVertex(int index, ofDefaultVec3 v){
	if(index > 3){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		return;
	}

	mesh.setVertex(index, v);
	ofNotifyEvent(vertexChangedEvent, index, this);
}

void QuadSurface::setVertices(vector<ofDefaultVec3> v){
	if(v.size() != 4){
		throw runtime_error("Wrong number of vertices (expected 4"); //, got " << v.size() << ")");
	}
	
	for(int i = 0; i < 4; ++i){
		mesh.setVertex(i, v[i]);
	}
	
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

void QuadSurface::setTexCoord(int index, ofDefaultVec2 t){
	if(index > 3){
		ofLog() << "Texture coordinate with this index does not exist: " << index
				<< endl;
		return;
	}

	mesh.setTexCoord(index, t);
}

void QuadSurface::setTexCoords(vector<ofDefaultVec2> t){
	if(t.size() != 4){
		throw runtime_error("Wrong number of vertices");
	}
	for(int i = 0; i < 4; ++i){
		mesh.setTexCoord(i, t[i]);
	}
}

void QuadSurface::moveBy(ofDefaultVec2 v){
	vector <ofDefaultVec3> & vertices = getVertices();
	
	for(int i = 0; i < vertices.size(); i++){
		vertices[i] += ofDefaultVec3(v.x, v.y, 0);
	}
	
	setMoved(true);
	ofNotifyEvent(verticesChangedEvent, mesh.getVertices(), this);
}

int QuadSurface::getType(){
	return SurfaceType::QUAD_SURFACE;
}

bool QuadSurface::hitTest(ofDefaultVec2 p){
	// Construct ofPolyline from vertices
	ofPolyline line = getHitArea();

	if(line.inside(p.x, p.y)){
		return true;
	}else{
		return false;
	}
}

ofDefaultVec3 QuadSurface::getVertex(int index){
	if(index > 3){
		ofLog() << "Vertex with this index does not exist: " << index << endl;
		throw runtime_error("Vertex index out of bounds.");
	}

	return mesh.getVertex(index);
}

ofDefaultVec2 QuadSurface::getTexCoord(int index){
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
	vector <ofDefaultVec2> & texCoords = mesh.getTexCoords();
	ofDefaultVec2 textureSize = ofDefaultVec2(source->getTexture()->getWidth(), source->getTexture()->getHeight());
	for(int i = 0; i < texCoords.size(); i++){
		line.addVertex(ofPoint(texCoords[i] * textureSize));
	}
	line.close();

	return line;
}

vector <ofDefaultVec3> & QuadSurface::getVertices(){
	// return only joint vertices
	return mesh.getVertices();
}

vector <ofDefaultVec2> & QuadSurface::getTexCoords(){
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
	
	ofDefaultVec3 p0 = mesh.getVertex(0);
	ofDefaultVec3 p1 = mesh.getVertex(1);
	ofDefaultVec3 p2 = mesh.getVertex(2);
	ofDefaultVec3 p3 = mesh.getVertex(3);

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
