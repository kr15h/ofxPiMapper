#include "ofApp.h"

void ofApp::setup()
{
    image.loadImage("TestPatternInvert.jpg");
    bShowInfo = false;
    
    /*
    surfaceManager.addSurface( ofxSurfaceType::TRIANGLE_SURFACE );
    
    surfaceManager.addSurface( ofxSurfaceType::TRIANGLE_SURFACE );
    surfaceManager.getSurface(1)->setVertex(0, ofVec2f(10, 10));
    surfaceManager.getSurface(1)->setVertex(1, ofVec2f(400, 20));
    surfaceManager.getSurface(1)->setVertex(2, ofVec2f(300, 400));
    */
    
    surfaceManager.loadXmlSettings("surfaces.xml");
    
    gui.setSurfaceManager( &surfaceManager );
}

void ofApp::update()
{
	ofBackground(0);
    
    ofVec2f p;
    p.x = ofRandomWidth();
    p.y = ofRandomHeight();
    //surfaceManager.getSurface(1)->setVertex(0, p);
    //triangleSurface.setVertex(0, p);
    
    ofVec2f t;
    t.x = ofRandomuf();
    t.y = ofRandomuf();
    //surfaceManager.getSurface(1)->setTexCoord(0, t);
    //triangleSurface.setTexCoord(0, t);
    
    //surfaceManager.update();
}

void ofApp::draw()
{
    //surfaceManager.draw();
    // if using gui - use ofxSurfaceManagerGui::draw() instead of surfaceManager::draw()
    gui.draw();
    
    if ( bShowInfo ) {
        // Draw instructions
        stringstream ss;
        ss << "There are 3 modes:\n\n";
        ss << " 1. Presentation mode\n";
        ss << " 2. Texture mapping mode\n";
        ss << " 3. Projection mapping mode\n";
        ss << " 4. Source selection mode\n\n";
        ss << "You can switch between the modes by using <1>, <2>, <3> and <4> keys on the keyboard.\n\n";
        ss << "Hit <i> to hide this message.";
        
        ofDrawBitmapStringHighlight(ss.str(), 10, 20, ofColor(0,0,0,100), ofColor(255,255,255,200));
    }
}

void ofApp::keyPressed(int key)
{
	cout << "Key pressed: " << static_cast<char>(key) << endl;
    
    switch (key) {
        case '1': gui.setMode(ofxGuiMode::NONE); break;
        case '2': gui.setMode(ofxGuiMode::TEXTURE_MAPPING); break;
        case '3': gui.setMode(ofxGuiMode::PROJECTION_MAPPING); break;
        case '4': gui.setMode(ofxGuiMode::SOURCE_SELECTION); break;
        case 'i': bShowInfo = !bShowInfo; break;
        case 'r': addRandomSurface(); break;
        case 'n': addSurface(); break;
        case 'f': ofToggleFullscreen(); break;
        case 's': surfaceManager.saveXmlSettings("surfaces.xml"); break;
        default: break;
    }
}

void ofApp::mousePressed(int x, int y, int button)
{
    //cout << "Mouse pressed." << endl;
    //surfaceManager.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button)
{
    //cout << "Mouse released." << endl;
    //surfaceManager.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button)
{
    //
    //surfaceManager.mouseDragged(x, y, button);
}

void ofApp::addRandomSurface()
{
    int surfaceType = ofxSurfaceType::TRIANGLE_SURFACE;
    vector<ofVec2f> vertices;
    vertices.push_back( ofVec2f( ofRandomWidth(), ofRandomHeight() ) );
    vertices.push_back( ofVec2f( ofRandomWidth(), ofRandomHeight() ) );
    vertices.push_back( ofVec2f( ofRandomWidth(), ofRandomHeight() ) );
    vector<ofVec2f> texCoords;
    texCoords.push_back( ofVec2f( ofRandomuf(), ofRandomuf() ) );
    texCoords.push_back( ofVec2f( ofRandomuf(), ofRandomuf() ) );
    texCoords.push_back( ofVec2f( ofRandomuf(), ofRandomuf() ) );
    surfaceManager.addSurface(surfaceType, vertices, texCoords);
    
    // select this surface right away
    surfaceManager.selectSurface(surfaceManager.size()-1);
}

void ofApp::addSurface()
{
    int surfaceType = ofxSurfaceType::TRIANGLE_SURFACE;
    vector<ofVec2f> vertices;
    vertices.push_back( ofVec2f( (float)ofGetWidth()/2.0f, 0.0f ) );
    vertices.push_back( ofVec2f( (float)ofGetWidth(), (float)ofGetHeight() ) );
    vertices.push_back( ofVec2f( 0.0f, (float)ofGetHeight() ) );
    vector<ofVec2f> texCoords;
    texCoords.push_back( ofVec2f( 0.5f, 0.0f ) );
    texCoords.push_back( ofVec2f( 1.0f, 1.0f ) );
    texCoords.push_back( ofVec2f( 0.0f, 1.0f ) );
    surfaceManager.addSurface(surfaceType, vertices, texCoords);
    
    // select this surface right away
    surfaceManager.selectSurface(surfaceManager.size()-1);
}