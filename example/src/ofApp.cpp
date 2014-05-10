#include "ofApp.h"

void ofApp::setup()
{
    image.loadImage("TestPatternInvert.jpg");
    
    triangleSurface.setup(ofVec2f(30,40), ofVec2f(500,500), ofVec2f(0,600),
                          ofVec2f(0,0), ofVec2f(1,1), ofVec2f(0,1),
                          &image.getTextureReference());
    
    gui.setup(triangleSurface);
    
    bShowInfo = true;
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
    
    gui.update();
}

void ofApp::draw()
{
    // Check GUI mode - we want to see the texture that we are editing
    // together with the actual surface being projection mapped.
    
    ofxSurfaceGui::editMode mode = gui.getMode();
    if ( mode == ofxSurfaceGui::TEXTURE_MAPPING ) {
        // Draw texture of the surface in the background
        //triangleSurface.getTexture()->draw(ofPoint(0,0));
        triangleSurface.drawTexture(ofVec2f(0, 0));
        
        // Make the triangle surface transparent but still visible
        // while we map the texture coordinates.
        ofPushStyle();
        ofSetColor(255, 255, 255, 200);
    }
    
    triangleSurface.draw();
    
    if ( mode == ofxSurfaceGui::TEXTURE_MAPPING ) {
        ofPopStyle();
    }
    
    gui.draw();
    
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
        case '1': gui.setMode(ofxSurfaceGui::NONE); break;
        case '2': gui.setMode(ofxSurfaceGui::TEXTURE_MAPPING); break;
        case '3': gui.setMode(ofxSurfaceGui::PROJECTION_MAPPING); break;
        case 'i': bShowInfo = !bShowInfo; break;
        default: break;
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    //cout << "Mouse pressed." << endl;
    gui.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button)
{
    //cout << "Mouse released." << endl;
    gui.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button)
{
    //
    gui.mouseDragged(x, y, button);
}