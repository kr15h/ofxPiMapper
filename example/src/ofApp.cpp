#include "ofApp.h"

void ofApp::setup() {
  bShowInfo = false;

  // check if the surfaces.xml file is there
  // if not - load defaultSurfaces.xml
  if (ofFile::doesFileExist("surfaces.xml")) {
    surfaceManager.loadXmlSettings("surfaces.xml");
  } else {
    surfaceManager.loadXmlSettings("defaultSurfaces.xml");
  }

  // Pass the surface manager to the mapper graphical user interface
  gui.setSurfaceManager(&surfaceManager);

  // Create FBO
  fbo = new ofFbo();
  fbo->allocate(500, 500);
  setFboAsTexture();

  // Genereate rects
  int numRects = 20;  // change this to add more or less rects
  for (int i = 0; i < numRects; i++) {
    rects.push_back(ofRectangle(0, ofRandom(fbo->getHeight()), fbo->getWidth(),
                                ofRandom(20)));
    rectSpeeds.push_back((1.0f + ofRandom(5)));
  }
  ofLog() << "Number of Images: " << mediaServer.getNumImages();
  ofLog() << "Number of Videos: " << mediaServer.getNumVideos();
  for (auto s : mediaServer.getImagePaths()) {
    ofLog() << s;
  }
  for (auto s : mediaServer.getVideoPaths()) {
    ofLog() << s;
  }
}

void ofApp::update() {
  // Move rects
  for (int i = 0; i < rects.size(); i++) {
    rects[i].y += rectSpeeds[i];
    if (rects[i].y > fbo->getHeight()) {
      rects[i].y = -rects[i].getHeight();
    }
  }

  // Fill FBO
  fbo->begin();
  ofClear(0);
  ofBackground(0);
  ofSetColor(255);
  for (int i = 0; i < rects.size(); i++) {
    ofRect(rects[i]);
  }
  fbo->end();
}

void ofApp::draw() {
  // Draw the piMapper GUI
  gui.draw();

  if (bShowInfo) {
    // Draw instructions
    stringstream ss;
    ss << "There are 4 modes:\n\n";
    ss << " 1. Presentation mode\n";
    ss << " 2. Texture mapping mode\n";
    ss << " 3. Projection mapping mode\n";
    ss << " 4. Source selection mode\n\n";
    ss << "You can switch between the modes by using <1>, <2>, <3> and <4> "
          "keys on the keyboard.\n\n";
    ss << "Press <r> or <n> to add random or normal surface.\n";
    ss << "Press <q> to add a new quad surface.\n";
    ss << "Press <s> to save the composition.\n";
    ss << "Press <f> to toggle fullscreen.\n";
    ss << "Press <a> to reassign the fbo texture to the first surface\n";
    ss << "Hit <i> to hide this message.";

    ofDrawBitmapStringHighlight(ss.str(), 10, 20, ofColor(0, 0, 0, 100),
                                ofColor(255, 255, 255, 200));
  }
}

void ofApp::exit() {
  // Clear FBO from mem
  delete fbo;
}

void ofApp::keyPressed(int key) {
  cout << "Key pressed: " << static_cast<char>(key) << endl;

  switch (key) {
    case '1':
      gui.setMode(ofx::piMapper::GuiMode::NONE);
      break;
    case '2':
      gui.setMode(ofx::piMapper::GuiMode::TEXTURE_MAPPING);
      break;
    case '3':
      gui.setMode(ofx::piMapper::GuiMode::PROJECTION_MAPPING);
      break;
    case '4':
      gui.setMode(ofx::piMapper::GuiMode::SOURCE_SELECTION);
      break;
    case 'i':
      bShowInfo = !bShowInfo;
      break;
    case 'r':
      addRandomSurface();
      break;
    case 'q':
      addQuadSurface();
      break;
    case 'n':
      addSurface();
      break;
    case 'f':
      ofToggleFullscreen();
      break;
    case 's':
      surfaceManager.saveXmlSettings("surfaces.xml");
      break;
    case 'a':
      setFboAsTexture();
      break;
    case OF_KEY_BACKSPACE:
      surfaceManager.removeSelectedSurface();
      break;
    default:
      break;
  }
}

void ofApp::addRandomSurface() {
  int surfaceType = ofx::piMapper::SurfaceType::TRIANGLE_SURFACE;
  vector<ofVec2f> vertices;
  vertices.push_back(ofVec2f(ofRandomWidth(), ofRandomHeight()));
  vertices.push_back(ofVec2f(ofRandomWidth(), ofRandomHeight()));
  vertices.push_back(ofVec2f(ofRandomWidth(), ofRandomHeight()));
  vector<ofVec2f> texCoords;
  texCoords.push_back(ofVec2f(ofRandomuf(), ofRandomuf()));
  texCoords.push_back(ofVec2f(ofRandomuf(), ofRandomuf()));
  texCoords.push_back(ofVec2f(ofRandomuf(), ofRandomuf()));
  surfaceManager.addSurface(surfaceType, vertices, texCoords);

  // select this surface right away
  surfaceManager.selectSurface(surfaceManager.size() - 1);
}

void ofApp::addQuadSurface() {
  int surfaceType = ofx::piMapper::SurfaceType::QUAD_SURFACE;
  vector<ofVec2f> vertices;

  int border = 50;
  vertices.push_back(ofVec2f(border, border));
  vertices.push_back(ofVec2f(ofGetWidth() - border, border));
  vertices.push_back(ofVec2f(ofGetWidth() - border, ofGetHeight() - border));
  vertices.push_back(ofVec2f(border, ofGetHeight() - border));

  vector<ofVec2f> texCoords;
  texCoords.push_back(ofVec2f(ofVec2f(0.0f, 0.0f)));
  texCoords.push_back(ofVec2f(ofVec2f(1.0f, 0.0f)));
  texCoords.push_back(ofVec2f(ofVec2f(1.0f, 1.0f)));
  texCoords.push_back(ofVec2f(ofVec2f(0.0f, 1.0f)));

  surfaceManager.addSurface(surfaceType, vertices, texCoords);

  // select this surface right away
  surfaceManager.selectSurface(surfaceManager.size() - 1);
}

void ofApp::addSurface() {
  int surfaceType = ofx::piMapper::SurfaceType::TRIANGLE_SURFACE;
  vector<ofVec2f> vertices;
  vertices.push_back(ofVec2f((float)ofGetWidth() / 2.0f, 0.0f));
  vertices.push_back(ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));
  vertices.push_back(ofVec2f(0.0f, (float)ofGetHeight()));
  vector<ofVec2f> texCoords;
  texCoords.push_back(ofVec2f(0.5f, 0.0f));
  texCoords.push_back(ofVec2f(1.0f, 1.0f));
  texCoords.push_back(ofVec2f(0.0f, 1.0f));
  surfaceManager.addSurface(surfaceType, vertices, texCoords);

  // select this surface right away
  surfaceManager.selectSurface(surfaceManager.size() - 1);
}

void ofApp::setFboAsTexture() {
  surfaceManager.getSurface(0)->setTexture(&fbo->getTextureReference());
}