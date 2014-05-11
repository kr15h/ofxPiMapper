#include "ofApp.h"

void ofApp::setup()
{
    image.loadImage("TestPatternInvert.jpg");
    bShowInfo = false;
    
    surfaceManager.addSurface();
}

void ofApp::update()
{
	ofBackground(0);
    
    ofVec2f p;
    p.x = ofRandomWidth();
    p.y = ofRandomHeight();
    //triangleSurface.setVertex(0, p);
    
    ofVec2f t;
    t.x = ofRandomuf();
    t.y = ofRandomuf();
    //triangleSurface.setTexCoord(0, t);
    
    surfaceManager.update();
}

void ofApp::draw()
{
    surfaceManager.draw();
    
    if ( bShowInfo ) {
        // Draw instructions
        stringstream ss;
        ss << "There are 3 modes:\n\n";
        ss << " 1. Presentation mode\n";
        ss << " 2. Texture mapping mode\n";
        ss << " 3. Projection mapping mode\n\n";
        ss << "You can switch between the modes by using <1>, <2> and <3> keys on the keyboard.\n\n";
        ss << "Hit <i> to hide this message.";
        
        ofDrawBitmapStringHighlight(ss.str(), 10, 20, ofColor(0,0,0,100), ofColor(255,255,255,200));
    }
}

void ofApp::keyPressed(int key)
{
	cout << "Key pressed: " << static_cast<char>(key) << endl;
    
    switch (key) {
        case '1': surfaceManager.setGuiMode(ofxSurfaceGui::NONE); break;
        case '2': surfaceManager.setGuiMode(ofxSurfaceGui::TEXTURE_MAPPING); break;
        case '3': surfaceManager.setGuiMode(ofxSurfaceGui::PROJECTION_MAPPING); break;
        case 'i': bShowInfo = !bShowInfo; break;
        default: break;
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    //cout << "Mouse pressed." << endl;
    surfaceManager.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button)
{
    //cout << "Mouse released." << endl;
    surfaceManager.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button)
{
    //
    surfaceManager.mouseDragged(x, y, button);
}