#include "ofApp.h"

void ofApp::setup()
{
	cout << "Hello World!" << endl;
}

void ofApp::update()
{
	ofBackground(0);
}

void ofApp::draw()
{
	ofRect(100, 100, ofGetWidth()-200, ofGetHeight()-200);
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