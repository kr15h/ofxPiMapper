#include "SourcesEditor.h"

namespace ofx {
namespace piMapper {
  SourcesEditor::SourcesEditor() {
    init();
    
    // Create new MediaServer instance,
    // we will need to clear this in the deconstr
    mediaServer = new MediaServer();
    isMediaServerExternal = false;
  }
  
  SourcesEditor::SourcesEditor(MediaServer* externalMediaServer) {
    init();
    
    // Assign external MediaServer instance pointer
    mediaServer = externalMediaServer;
    isMediaServerExternal = true;
  }

  SourcesEditor::~SourcesEditor() {
    unregisterAppEvents();
    delete gui;
    while (images.size()) {
      delete images.back();
      images.pop_back();
    }
    
    // If mediaServer is local, clear it
    if (isMediaServerExternal) {
      // Clear all loaded sources
      //mediaServer->clear()
      // Destroy the pointer and set it to NULL pointer
      delete mediaServer;
      mediaServer = NULL;
    }
  }
  
  // Initialize instance variables
  void SourcesEditor::init() {
    mediaServer = NULL;
    isMediaServerExternal = false;
    defImgDir = DEFAULT_IMAGES_DIR;
    registerAppEvents();
  }
  
  void SourcesEditor::registerAppEvents() {
    ofAddListener(ofEvents().setup, this, &SourcesEditor::setup);
  }

  void SourcesEditor::unregisterAppEvents() {
    ofRemoveListener(ofEvents().setup, this, &SourcesEditor::setup);
  }

  void SourcesEditor::setup(ofEventArgs& args) {
    gui = new RadioList();

    // read directory contents
    ofDirectory imgDir;
    imgDir.listDir(defImgDir);
    imgDir.sort();

    vector<string> vnames;

    for (int i = 0; i < (int)imgDir.size(); i++) {
      // images[i].loadImage(imgDir.getPath(i));
      vnames.push_back(imgDir.getName(i));
    }

    gui->setup("Images", vnames);
    gui->setPosition(20, 20);
    ofAddListener(gui->radioSelectedEvent, this, &SourcesEditor::guiEvent);
  }

  void SourcesEditor::draw() {
    // Don't draw if there is no source selected
    if (surfaceManager->getSelectedSurface() == NULL) {
      return;
    }

    gui->draw();
  }

  void SourcesEditor::loadImage(string name, string path) {
    images.push_back(new ofImage());
    images.back()->loadImage(path);

    imageNames.push_back(name);

    ofSendMessage("imageLoaded");
  }

  void SourcesEditor::disable() { gui->disable(); }

  void SourcesEditor::enable() {
    // Don't enable if there is no surface selected
    if (surfaceManager->getSelectedSurface() == NULL) {
      cout << "No surface selected. Not enable()ing source list." << endl;
      return;
    }

    gui->enable();
  }

  void SourcesEditor::setSurfaceManager(SurfaceManager* newSurfaceManager) {
    surfaceManager = newSurfaceManager;
  }

  void SourcesEditor::selectImageSourceRadioButton(string name) {
    if (name == "none") {
      gui->unselectAll();
      return;
    } else {
      int i;
      for (i = 0; i < gui->size(); i++) {
        if (gui->getItemName(i) == name) {
          gui->selectItem(i);
          return;
        }
      }
    }
  }

  int SourcesEditor::getLoadedTexCount() { return images.size(); }

  ofTexture* SourcesEditor::getTexture(int index) {
    if (index >= images.size()) {
      throw std::runtime_error("Texture index out of bounds.");
    }

    return &images[index]->getTextureReference();
  }

  void SourcesEditor::guiEvent(string& imageName) {
    string name = imageName;

    if (surfaceManager->getSelectedSurface() == NULL) {
      return;
    }

    stringstream ss;
    ss << defImgDir << name;
    cout << "attempt to load image: " << ss.str() << endl;
    ofTexture* texture = surfaceManager->loadImageSource(name, ss.str());
    surfaceManager->getSelectedSurface()->setTexture(texture);
    surfaceManager->manageMemory();
  }
}
}