#include "ofxTriangleSurface.h"

ofxTriangleSurface::ofxTriangleSurface()
{
	cout << "ofxTriangleSurface constructor." << endl;
    setup();
}

ofxTriangleSurface::~ofxTriangleSurface()
{
	cout << "ofxTriangleSurface destructor." << endl;
}

void ofxTriangleSurface::setup()
{
    // Create 3 points for the triangle
    ofVec2f p1 = ofVec2f(ofGetWidth()/2.0f, 0);
    ofVec2f p2 = ofVec2f(ofVec2f(0, ofGetHeight()));
    ofVec2f p3 = ofVec2f(ofGetWidth(), ofGetHeight());
    
    // Create 3 point for the texture coordinates
    ofVec2f t1 = ofVec2f(0.5f, 0);
    ofVec2f t2 = ofVec2f(0, 1.0f);
    ofVec2f t3 = ofVec2f(1, 1.0f);
    
    setup( p1, p2, p3, t1, t2, t3, texture );
}

void ofxTriangleSurface::setup( ofVec2f p1, ofVec2f p2, ofVec2f p3, ofVec2f t1, ofVec2f t2, ofVec2f t3, ofTexture* texturePtr )
{
    // Assign texture
    texture = texturePtr;
    
    // Clear mesh
    mesh.clear();
    
    // Create a surface with the points
    mesh.addVertex( p1 );
    mesh.addVertex( p2 );
    mesh.addVertex( p3 );
    
    // Add texture coordinates
    mesh.addTexCoord(t1);
    mesh.addTexCoord(t2);
    mesh.addTexCoord(t3);
}

void ofxTriangleSurface::draw()
{
    texture->bind();
    mesh.draw();
    texture->unbind();
}

void ofxTriangleSurface::setVertex(int index, ofVec2f p)
{
    if ( index > 2 ) {
        ofLog() << "Vertex with this index does not exist: " << index << endl;
        return;
    }
    
    mesh.setVertex(index, p);
}