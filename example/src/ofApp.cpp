#include "ofApp.h"

void ofApp::setup()
{
    // Create a triangle surface
    triangleSurface.setup( ofVec2f(30,40), ofVec2f(500,500), ofVec2f(0,600) );
}

void ofApp::update()
{
	ofBackground(0);
}

void ofApp::draw()
{
    triangleSurface.draw();
}

void ofApp::keyPressed(int key)
{
	cout << "Key pressed: " << static_cast<char>(key) << endl;
}

void ofApp::mousePressed(int x, int y, int button)
{
    cout << "Mouse pressed." << endl;
}

void ofApp::mouseReleased(int x, int y, int button)
{
    cout << "Mouse released." << endl;
}

void ofApp::mouseDragged(int x, int y, int button)
{
    //
}