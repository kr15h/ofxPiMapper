#include "SourcesEditor.h"

namespace ofx {
namespace piMapper {
  SourcesEditor::SourcesEditor() {
    init();
    
    // Create new MediaServer instance,
    // we will need to clear this in the deconstr
    mediaServer = new MediaServer();
    isMediaServerExternal = false;
    
    cout << "numImages: " << mediaServer->getNumImages() << endl;
    /*
    cout << "list: " << endl;
    for (int i = 0; i < mediaServer->getNumImages(); i++) {
      cout << mediaServer->getImagePaths()[i] << endl;
    }
    */
    
    cout << "numVideos: " << mediaServer->getNumVideos() << endl;
    /*
    cout << "list: " << endl;
    for (int i = 0; i < mediaServer->getNumVideos(); i++) {
      cout << mediaServer->getImagePaths()[i] << endl;
    }
    */
    
    addMediaServerListeners();
    
    // Test media server onImageLoaded event
    /*
    if (mediaServer->getNumImages()) {
      mediaServer->loadImage(mediaServer->getImagePaths()[0]);
    }
    */
    
  }
  
  SourcesEditor::SourcesEditor(MediaServer* externalMediaServer) {
    init();
    
    // Assign external MediaServer instance pointer
    mediaServer = externalMediaServer;
    isMediaServerExternal = true;
    addMediaServerListeners();
  }

  SourcesEditor::~SourcesEditor() {
    unregisterAppEvents();
    delete gui;
    while (images.size()) {
      delete images.back();
      images.pop_back();
    }
    
    removeMediaServerListeners();
    clearMediaServer();
  }
  
  void SourcesEditor::registerAppEvents() {
    ofAddListener(ofEvents().setup, this, &SourcesEditor::setup);
  }

  void SourcesEditor::unregisterAppEvents() {
    ofRemoveListener(ofEvents().setup, this, &SourcesEditor::setup);
  }

  void SourcesEditor::setup(ofEventArgs& args) {
    gui = new RadioList();
    // Get image names from media server
    vector<string> vnames = mediaServer->getImageNames();
    gui->setup("Images", vnames, mediaServer->getImagePaths());
    gui->setPosition(20, 20);
    // Add radio selected event listener so we can load sources
    ofAddListener(gui->onRadioSelected, this, &SourcesEditor::handleRadioSelected);
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
  
  void SourcesEditor::setMediaServer(MediaServer* newMediaServer) {
    // If the new media server is not valid
    if (newMediaServer == NULL) {
      // Log an error and return from the routine
      ofLogFatalError("SourcesEditor") << "New media server is NULL";
      std::exit(EXIT_FAILURE);
    }
    // Attempt to clear existing media server and assign new one
    clearMediaServer();
    cout << "old ms addr: " << mediaServer << endl;
    cout << "new ms addr: " << newMediaServer << endl;
    mediaServer = newMediaServer;
    isMediaServerExternal = true;
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
  
  void SourcesEditor::init() {
    mediaServer = NULL; // Pointers to NULL pointer so we can check later
    isMediaServerExternal = false;
    defImgDir = DEFAULT_IMAGES_DIR;
    registerAppEvents();
  }
  
  void SourcesEditor::addMediaServerListeners() {
    // Check if the media server is valid
    if (mediaServer == NULL) {
      ofLogError("SourcesEditor::addMediaServerListeners", "Media server not set");
      return;
    }
    
    // Add listeners to custom events of the media server
    ofAddListener(mediaServer->onImageAdded, this, &SourcesEditor::handleImageAdded);
    ofAddListener(mediaServer->onImageRemoved, this, &SourcesEditor::handleImageRemoved);
    ofAddListener(mediaServer->onVideoAdded, this, &SourcesEditor::handleVideoAdded);
    ofAddListener(mediaServer->onVideoRemoved, this, &SourcesEditor::handleVideoRemoved);
    ofAddListener(mediaServer->onImageLoaded, this, &SourcesEditor::handleImageLoaded);
    ofAddListener(mediaServer->onImageUnloaded, this, &SourcesEditor::handleImageUnloaded);
    
  }
  
  void SourcesEditor::removeMediaServerListeners() {
    // Check if the media server is valid
    if (mediaServer == NULL) {
      ofLogError("SourcesEditor::addMediaServerListeners", "Media server not set");
      return;
    }
    
    // Remove listeners to custom events of the media server
    ofRemoveListener(mediaServer->onImageAdded, this, &SourcesEditor::handleImageAdded);
    ofRemoveListener(mediaServer->onImageRemoved, this, &SourcesEditor::handleImageRemoved);
    ofRemoveListener(mediaServer->onVideoAdded, this, &SourcesEditor::handleVideoAdded);
    ofRemoveListener(mediaServer->onVideoRemoved, this, &SourcesEditor::handleVideoRemoved);
    ofRemoveListener(mediaServer->onImageLoaded, this, &SourcesEditor::handleImageLoaded);
    ofRemoveListener(mediaServer->onImageUnloaded, this, &SourcesEditor::handleImageUnloaded);
  }

  void SourcesEditor::handleRadioSelected(string& sourcePath) {
    BaseSurface* surface = surfaceManager->getSelectedSurface();
    if (surface == NULL) {
      return;
    }
    BaseSource* source = surface->getSource();
    if (source->isLoadable()) {
      mediaServer->unloadMedia(source->getPath());
    }
    surface->setSource(mediaServer->loadImage(sourcePath));
  }
  
  void SourcesEditor::clearMediaServer() {
    // If mediaServer is local, clear it
    if (!isMediaServerExternal) {
      // Clear all loaded sources
      mediaServer->clear();
      // Destroy the pointer and set it to NULL pointer
      delete mediaServer;
      mediaServer = NULL;
    }
  }
  
  void SourcesEditor::handleImageAdded(string& path) {
    cout << "image added: " << path << endl;
  }
  
  void SourcesEditor::handleImageRemoved(string& path) {
    cout << "image removed: " << path << endl;
  }
  
  void SourcesEditor::handleVideoAdded(string& path) {
    cout << "video added: " << path << endl;
  }
  
  void SourcesEditor::handleVideoRemoved(string& path) {
    cout << "video removed: " << path << endl;
  }
  
  void SourcesEditor::handleImageLoaded(string& path) {
    cout << "Image loaded: " << path << endl;
    
    // Test image unload
    // mediaServer->unloadImage(path);
    
    BaseSource* source = mediaServer->getSourceByPath(path);
    surfaceManager->getSelectedSurface()->setSource(source);
  }
  
  void SourcesEditor::handleImageUnloaded(string& path) {
    cout << "Image unloaded: " << path << endl;
  }
}
}