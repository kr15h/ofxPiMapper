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
    // Get image names from media server
    vector<string> imageNames = mediaServer->getImageNames();
    imageSelector->setup("Images", imageNames, mediaServer->getImagePaths());
    imageSelector->setPosition(20, 20);
    ofAddListener(imageSelector->onRadioSelected, this, &SourcesEditor::handleImageSelected);
    vector<string> videoNames = mediaServer->getVideoNames();
    videoSelector->setup("Videos", videoNames, mediaServer->getVideoPaths());
    videoSelector->setPosition(250, 20);
    ofAddListener(videoSelector->onRadioSelected, this, &SourcesEditor::handleVideoSelected);
  }

  void SourcesEditor::draw() {
    // Don't draw if there is no source selected
    if (surfaceManager->getSelectedSurface() == NULL) {
      ofLogNotice("SourcesEditor") << "No surface selected";
      return;
    }
    imageSelector->draw();
    videoSelector->draw();
  }

  void SourcesEditor::disable() {
    imageSelector->disable();
    videoSelector->disable();
  }

  void SourcesEditor::enable() {
    // Don't enable if there is no surface selected
    if (surfaceManager->getSelectedSurface() == NULL) {
      ofLogNotice("SourcesEditor") << "No surface selected. Not enabling and not showing source list.";
      return;
    }
    imageSelector->enable();
    videoSelector->enable();
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
      imageSelector->unselectAll();
      videoSelector->unselectAll();
      return;
    } else {
      // Check image selector first
      bool imageRadioSelected = imageSelector->selectItemByValue(sourcePath);
      bool videoRadioSelected = videoSelector->selectItemByValue(sourcePath);
      if (imageRadioSelected || videoRadioSelected) {
        return;
      }
      // Log warning if we are still here
      ofLogWarning("SourcesEditor") << "Could not find option in any of the source lists";
    }
  }
  
  void SourcesEditor::init() {
    mediaServer = NULL; // Pointers to NULL pointer so we can check later
    isMediaServerExternal = false;
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

  void SourcesEditor::handleImageSelected(string& imagePath) {
    // Unselect video item if any selected
    videoSelector->unselectAll();
    BaseSurface* surface = surfaceManager->getSelectedSurface();
    if (surface == NULL) {
      ofLogNotice("SourcesEditor") << "No surface selected";
      return;
    }
    // Unload old media
    BaseSource* source = surface->getSource();
    if (source->isLoadable()) {
      mediaServer->unloadMedia(source->getPath());
    }
    // Load new image
    surface->setSource(mediaServer->loadImage(imagePath));
  }
  
  void SourcesEditor::handleVideoSelected(string& videoPath) {
    // Unselect image item if any selected
    imageSelector->unselectAll();
    BaseSurface* surface = surfaceManager->getSelectedSurface();
    if (surface == NULL) {
      ofLogNotice("SourcesEditor") << "No surface selected";
      return;
    }
    // Unload old media
    BaseSource* source = surface->getSource();
    if (source->isLoadable()) {
      mediaServer->unloadMedia(source->getPath());
    }
    // Load new video
    surface->setSource(mediaServer->loadVideo(videoPath));
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
    
    //BaseSource* source = mediaServer->getSourceByPath(path);
    //surfaceManager->getSelectedSurface()->setSource(source);
  }
  
  void SourcesEditor::handleImageUnloaded(string& path) {
    cout << "Image unloaded: " << path << endl;
  }
}
}