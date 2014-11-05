#include "SourcesEditor.h"

namespace ofx {
namespace piMapper {
  SourcesEditor::SourcesEditor() {
    init();
    // Create new MediaServer instance,
    // we will need to clear this in the deconstr
    mediaServer = new MediaServer();
    isMediaServerExternal = false;
    addMediaServerListeners();
  }
  
  void SourcesEditor::init() {
    mediaServer = NULL; // Pointers to NULL pointer so we can check later
    isMediaServerExternal = false;
    registerAppEvents();
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
    delete imageSelector;
    delete videoSelector;
    delete fboSelector;
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
    imageSelector = new RadioList();
    videoSelector = new RadioList();
    fboSelector = new RadioList();
    
    // Get media count
    int numImages = mediaServer->getNumImages();
    int numVideos = mediaServer->getNumVideos();
    int numFbos = mediaServer->getNumFboSources();
    
    // Depending on media count, decide what to load and initialize
    if (numImages) {
      // Get image names from media server
      vector<string> imageNames = mediaServer->getImageNames();
      imageSelector->setup("Images", imageNames, mediaServer->getImagePaths());
      ofAddListener(imageSelector->onRadioSelected, this, &SourcesEditor::handleImageSelected);
    }
    if (numVideos) {
      vector<string> videoNames = mediaServer->getVideoNames();
      videoSelector->setup("Videos", videoNames, mediaServer->getVideoPaths());
      ofAddListener(videoSelector->onRadioSelected, this, &SourcesEditor::handleVideoSelected);
    }
    if (numFbos) {
      std::vector<std::string> fboNames = mediaServer->getFboSourceNames();
      fboSelector->setup("FBOs", fboNames, fboNames);
      ofAddListener(fboSelector->onRadioSelected, this, &SourcesEditor::handleFboSelected);
    }
    
    // Align menus
    int menuPosX = 20;
    int distX = 230;
    if (numImages) {
      imageSelector->setPosition(menuPosX, 20);
      menuPosX += distX;
    }
    if (numVideos) {
      videoSelector->setPosition(menuPosX, 20);
      menuPosX += distX;
    }
    if (numFbos) {
      fboSelector->setPosition(menuPosX, 20);
    }
    
  }

  void SourcesEditor::draw() {
    // Don't draw if there is no source selected
    if (surfaceManager->getSelectedSurface() == NULL) {
      ofLogNotice("SourcesEditor") << "No surface selected";
      return;
    }
    if (imageSelector->size()) {
      imageSelector->draw();
    }
    if (videoSelector->size()) {
      videoSelector->draw();
    }
    if (fboSelector->size()) {
      fboSelector->draw();
    }
    
  }

  void SourcesEditor::disable() {
    if (imageSelector->size()) {
      imageSelector->disable();
    }
    if (videoSelector->size()) {
      videoSelector->disable();
    }
    if (fboSelector->size()) {
      fboSelector->disable();
    }
  }

  void SourcesEditor::enable() {
    // Don't enable if there is no surface selected
    if (surfaceManager->getSelectedSurface() == NULL) {
      ofLogNotice("SourcesEditor") << "No surface selected. Not enabling and not showing source list.";
      return;
    }
    if (imageSelector->size()) {
      imageSelector->enable();
    }
    if (videoSelector->size()) {
      videoSelector->enable();
    }
    if (fboSelector->size()) {
      fboSelector->enable();
    }
    BaseSource* source = surfaceManager->getSelectedSurface()->getSource();
    selectSourceRadioButton(source->getPath());
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
    //cout << "old ms addr: " << mediaServer << endl;
    //cout << "new ms addr: " << newMediaServer << endl;
    mediaServer = newMediaServer;
    isMediaServerExternal = true;
  }

  void SourcesEditor::selectSourceRadioButton(std::string& sourcePath) {
    if (sourcePath == "") {
      ofLogNotice("SourcesEditor") << "Path is empty";
      if (imageSelector->size()) {
        imageSelector->unselectAll();
      }
      if (videoSelector->size()) {
        videoSelector->unselectAll();
      }
      if (fboSelector->size()) {
        fboSelector->unselectAll();
      }
      return;
    } else {
      // Check image selector first
      bool imageRadioSelected = false;
      bool videoRadioSelected = false;
      bool fboRadioSelected = false;
      if (imageSelector->size()) {
        imageRadioSelected = imageSelector->selectItemByValue(sourcePath);
      }
      if (videoSelector->size()) {
        videoRadioSelected = videoSelector->selectItemByValue(sourcePath);
      }
      if (fboSelector->size()) {
        fboRadioSelected = fboSelector->selectItemByValue(sourcePath);
      }
      if (imageRadioSelected || videoRadioSelected || fboRadioSelected) {
        return;
      }
      // Log warning if we are still here
      ofLogWarning("SourcesEditor") << "Could not find option in any of the source lists";
    }
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
    
    ofAddListener(mediaServer->onFboSourceAdded, this, &SourcesEditor::handleFboSourceAdded);
    ofAddListener(mediaServer->onFboSourceRemoved, this, &SourcesEditor::handleFboSourceRemoved);
    ofAddListener(mediaServer->onFboSourceLoaded, this, &SourcesEditor::handleFboSourceLoaded);
    ofAddListener(mediaServer->onFboSourceUnloaded, this, &SourcesEditor::handleFboSourceUnloaded);
    
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
    ofRemoveListener(mediaServer->onFboSourceAdded, this, &SourcesEditor::handleFboSourceAdded);
    ofRemoveListener(mediaServer->onFboSourceRemoved, this, &SourcesEditor::handleFboSourceRemoved);
    ofRemoveListener(mediaServer->onFboSourceLoaded, this, &SourcesEditor::handleFboSourceLoaded);
    ofRemoveListener(mediaServer->onFboSourceUnloaded, this, &SourcesEditor::handleFboSourceUnloaded);
  }

  void SourcesEditor::handleImageSelected(string& imagePath) {
    // Unselect selected items
    videoSelector->unselectAll();
    fboSelector->unselectAll();
    
    BaseSurface* surface = surfaceManager->getSelectedSurface();
    if (surface == NULL) {
      ofLogWarning("SourcesEditor") << "No surface selected";
      return;
    }
    
    // Unload old media
    BaseSource* source = surface->getSource();
    if (source->isLoadable()) {
      mediaServer->unloadMedia(source->getPath());
    } else {
      mediaServer->unloadMedia(source->getName());
    }

    // Load new image
    surface->setSource(mediaServer->loadImage(imagePath));
  }
  
  void SourcesEditor::handleVideoSelected(string& videoPath) {
    // Unselect any selected items
    fboSelector->unselectAll();
    imageSelector->unselectAll();
    
    BaseSurface* surface = surfaceManager->getSelectedSurface();
    if (surface == NULL) {
      ofLogWarning("SourcesEditor") << "No surface selected";
      return;
    }
    
    // Unload old media
    BaseSource* source = surface->getSource();
    if (source->isLoadable()) {
      mediaServer->unloadMedia(source->getPath());
    } else {
      mediaServer->unloadMedia(source->getName());
    }
    
    // Load new video
    surface->setSource(mediaServer->loadVideo(videoPath));
  }
  
  void SourcesEditor::handleFboSelected(string &fboName) {
    videoSelector->unselectAll();
    imageSelector->unselectAll();
    
    // Get selected surface
    BaseSurface* surface = surfaceManager->getSelectedSurface();
    if (surface == NULL) {
      ofLogWarning("SourcesEditor") << "No surface selected";
      return;
    }
    
    // Unload old media
    BaseSource* source = surface->getSource();
    if (source->isLoadable()) {
      mediaServer->unloadMedia(source->getPath());
    } else {
      mediaServer->unloadMedia(source->getName());
    }
    
    // Load new FBO
    surface->setSource(mediaServer->loadFboSource(fboName));
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
  
  void SourcesEditor::handleImageAdded(std::string& path) {}
  void SourcesEditor::handleImageRemoved(std::string& path) {}
  void SourcesEditor::handleVideoAdded(std::string& path) {}
  void SourcesEditor::handleVideoRemoved(std::string& path) {}
  void SourcesEditor::handleImageLoaded(std::string& path) {}
  void SourcesEditor::handleImageUnloaded(std::string& path) {}
  void SourcesEditor::handleFboSourceAdded(std::string& name) {}
  void SourcesEditor::handleFboSourceRemoved(std::string& name) {}
  void SourcesEditor::handleFboSourceLoaded(std::string& name) {}
  void SourcesEditor::handleFboSourceUnloaded(std::string& name) {}
  
}
}