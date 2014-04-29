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
    
    setup( p1, p2, p3 );
}

void ofxTriangleSurface::setup( ofVec2f p1, ofVec2f p2, ofVec2f p3 )
{
    // Clear previous vertices if any
    mesh.clear();
    
    // Create a surface with the points
    mesh.addVertex( p1 );
    mesh.addVertex( p2 );
    mesh.addVertex( p3 );
}

void ofxTriangleSurface::draw()
{
    mesh.draw();
}