#include "ofxPiMapper.h"

ofxPiMapper::ofxPiMapper(): bShowInfo(false), isSetUp(false){
    ofAddListener(ofEvents().keyPressed, this, &ofxPiMapper::keyPressed);
}

ofxPiMapper::~ofxPiMapper(){
    ofRemoveListener(ofEvents().keyPressed, this, &ofxPiMapper::keyPressed);
}

void ofxPiMapper::setup(){
    ofLogNotice("ofxPiMapper") << "Setting up...";
    
    // Assign media server to other pi mapper components
    surfaceManager.setMediaServer(&mediaServer);
    gui.setMediaServer(&mediaServer);
    gui.setCmdManager(&cmdManager);
    
    // Check if we have user surfaces defined, if not - load default
    if (ofFile::doesFileExist(PIMAPPER_USER_SURFACES_XML_FILE)){
        ofLogNotice("ofxPiMapper") << "Loading user surfaces from " << PIMAPPER_USER_SURFACES_XML_FILE;
        surfaceManager.loadXmlSettings(PIMAPPER_USER_SURFACES_XML_FILE);
    } else {
        ofLogNotice("ofxPiMapper") << "Loading default surfaces from " << PIMAPPER_DEF_SURFACES_XML_FILE;
        surfaceManager.loadXmlSettings(PIMAPPER_DEF_SURFACES_XML_FILE);
    }
    
    // The GUI needs something to interface with
    gui.setSurfaceManager(&surfaceManager);
    
    isSetUp = true;
    
    ofLogNotice("ofxPiMapper") << "Done setting up";
    
    _mainView = new ofx::piMapper::MainView();
    _keyboard = new ofx::piMapper::Keyboard(this);
}

void ofxPiMapper::stateSetup() {
    // TODO: test state imp
}

void ofxPiMapper::draw(){
    if (!isSetUp) {
        return;
    }
    
    // Draw the piMapper GUI
    gui.draw();
    
    if (bShowInfo){
        // Draw instructions
        stringstream ss;
        ss << "There are 4 modes:\n\n";
        ss << " 1. Presentation mode\n";
        ss << " 2. Texture mapping mode\n";
        ss << " 3. Projection mapping mode\n";
        ss << " 4. Source selection mode\n\n";
        ss << "You can switch between the modes by using <1>, <2>, <3> and <4> "
        "keys on the keyboard.\n\n";
        ss << "Press <t> to add new triangle surface\n";
        ss << "Press <q> to add new quad surface\n";
        ss << "Press <s> to save the composition\n";
        ss << "Press <f> to toggle fullscreen\n";
        ss << "Press <i> to hide this message";
        
        ofDrawBitmapStringHighlight(ss.str(), 10, 20, ofColor(0, 0, 0, 100),
                                                                ofColor(255, 255, 255, 200));
    }
    
    // TODO: remove undo test completely
    //ofDrawBitmapStringHighlight(ofToString(undoTestValue), 200, 200);
    
    _mainView->draw();
    
} // draw

void ofxPiMapper::keyPressed(ofKeyEventArgs &args){
    //ofLogNotice("ofxPiMapper") << "Key pressed: " << static_cast<char>(args.key);
    
    switch (args.key) {
        
        /*
        case '1':
            if (gui.getMode() != ofx::piMapper::GuiMode::NONE) {
                cmdManager.exec(new ofx::piMapper::SetGuiModeCmd(&gui,
                    ofx::piMapper::GuiMode::NONE));
            }
            break;
        case '2':
            if (gui.getMode() != ofx::piMapper::GuiMode::TEXTURE_MAPPING) {
                cmdManager.exec(new ofx::piMapper::SetGuiModeCmd(&gui,
                    ofx::piMapper::GuiMode::TEXTURE_MAPPING));
            }
            break;
        case '3':
            if (gui.getMode() != ofx::piMapper::GuiMode::PROJECTION_MAPPING) {
                cmdManager.exec(new ofx::piMapper::SetGuiModeCmd(&gui,
                    ofx::piMapper::GuiMode::PROJECTION_MAPPING));
            }
            break;
        case '4':
            if (gui.getMode() != ofx::piMapper::GuiMode::SOURCE_SELECTION) {
                cmdManager.exec(new ofx::piMapper::SetGuiModeCmd(&gui,
                    ofx::piMapper::GuiMode::SOURCE_SELECTION));
            }
            break;
        */
        case 'i':
            bShowInfo = !bShowInfo;
            break;
        case 'q':
            addQuadSurface();
            break;
        case 't':
            addTriangleSurface();
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case 's':
            surfaceManager.saveXmlSettings(PIMAPPER_USER_SURFACES_XML_FILE);
            break;
        case OF_KEY_BACKSPACE:
            cmdManager.exec(new ofx::piMapper::RmSurfaceCmd((ofxPiMapper *)this));
            break;
        case 'z':
            // Undo any undo command operation
            cmdManager.undo();
            break;
        default:
            break;
    }
} // keyPressed

void ofxPiMapper::addFboSource(ofx::piMapper::FboSource &fboSource){
    mediaServer.addFboSource(fboSource);
} // addFboSource

void ofxPiMapper::addTriangleSurface(){
    int surfaceType = ofx::piMapper::SurfaceType::TRIANGLE_SURFACE;
    
    vector<ofVec2f> vertices;
    float margin = 50.0f;
    vertices.push_back(ofVec2f((float)ofGetWidth() / 2.0f, margin));
    vertices.push_back(ofVec2f((float)ofGetWidth() - margin, (float)ofGetHeight() - margin));
    vertices.push_back(ofVec2f(margin, (float)ofGetHeight() - margin));
    
    vector<ofVec2f> texCoords;
    texCoords.push_back(ofVec2f(0.5f, 0.0f));
    texCoords.push_back(ofVec2f(1.0f, 1.0f));
    texCoords.push_back(ofVec2f(0.0f, 1.0f));
    surfaceManager.addSurface(surfaceType, vertices, texCoords);
    
    // Select this surface right away
    surfaceManager.selectSurface(surfaceManager.size() - 1);
    
} // addTriangleSurface

void ofxPiMapper::addQuadSurface(){
    
    int surfaceType = ofx::piMapper::SurfaceType::QUAD_SURFACE;
    
    vector<ofVec2f> vertices;
    float margin = 50.0f;
    vertices.push_back(ofVec2f(margin, margin));
    vertices.push_back(ofVec2f((float)ofGetWidth() - margin, margin));
    vertices.push_back(ofVec2f((float)ofGetWidth() - margin, (float)ofGetHeight() - margin));
    vertices.push_back(ofVec2f(margin, (float)ofGetHeight() - margin));
    
    vector<ofVec2f> texCoords;
    texCoords.push_back(ofVec2f(ofVec2f(0.0f, 0.0f)));
    texCoords.push_back(ofVec2f(ofVec2f(1.0f, 0.0f)));
    texCoords.push_back(ofVec2f(ofVec2f(1.0f, 1.0f)));
    texCoords.push_back(ofVec2f(ofVec2f(0.0f, 1.0f)));
    
    surfaceManager.addSurface(surfaceType, vertices, texCoords);
    
    // select this surface right away
    surfaceManager.selectSurface(surfaceManager.size() - 1);
    
} // addQuadSurface

ofx::piMapper::CmdManager & ofxPiMapper::getCmdManager() {
    return cmdManager;
}

ofx::piMapper::SurfaceManagerGui & ofxPiMapper::getGui() {
    return gui;
}

ofx::piMapper::MediaServer& ofxPiMapper::getMediaServer(){
    return mediaServer;
}

ofx::piMapper::SurfaceManager& ofxPiMapper::getSurfaceManager(){
    return surfaceManager;
}