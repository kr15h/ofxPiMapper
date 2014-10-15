//
//  MediaServer.cpp
//  example
//
//  Created by felix on 13.09.14.
//
//

#include "MediaServer.h"

namespace ofx {
namespace piMapper {

  MediaServer::MediaServer():
    videoWatcher(ofToDataPath(DEFAULT_VIDEOS_DIR, true), true),
    imageWatcher(ofToDataPath(DEFAULT_IMAGES_DIR, true), false) {
      addWatcherListeners();
  }

  MediaServer::~MediaServer() {
    removeWatcherListeners();
  };

  int MediaServer::getNumImages() { return imageWatcher.getFilePaths().size(); }
  int MediaServer::getNumVideos() { return videoWatcher.getFilePaths().size(); }

  std::vector<std::string>& MediaServer::getImagePaths() {
    return imageWatcher.getFilePaths();
  }
  std::vector<std::string>& MediaServer::getVideoPaths() {
    return videoWatcher.getFilePaths();
  }
  
  std::vector<std::string> MediaServer::getImageNames() {
    std::vector<std::string> imageNames;
    for (int i = 0; i < getNumImages(); i++) {
      // Split image path
      std::vector<std::string> pathParts = ofSplitString(getImagePaths()[i], "/");
      // And get only the last piece
      std::string name = pathParts[pathParts.size()-1];
      imageNames.push_back(name);
    }
    return imageNames;
  }
  
  void MediaServer::loadImage(string& path) {
    // Load image and add to vector if loading success
    ofImage image;
    if (image.loadImage(path)) {
      loadedImages.push_back(image);
      loadedImagePaths.push_back(path); // Save also path
      ofNotifyEvent(onImageLoaded, path, this);
    }
  }
  
  void MediaServer::unloadImage(string& path) {
    // Search for given path in loaded image paths
    for (int i = 0; i < loadedImagePaths.size(); i++) {
      // If found
      if (loadedImagePaths[i] == path) {
        // Remove path and unload image as well as remove it from storage
        loadedImagePaths.erase(loadedImagePaths.begin() + i);
        loadedImages[i].clear();
        loadedImages.erase(loadedImages.begin() + i);
        ofNotifyEvent(onImageUnloaded, path, this);
        break;
      }
    }
  }
  
  ofTexture* MediaServer::getImageTexture(string &path) {
    
    // Find image index by path
    for (int i = 0; i < loadedImagePaths.size(); i++) {
      if (path == loadedImagePaths[i]) {
        if (loadedImages[i].isAllocated()) {
          return &loadedImages[i].getTextureReference();
        }
      }
    }
    
    // If we havent returned yet, that means that there is no image
    // and we need to sort this out somehow
    ofLogError("MediaServer::getImageTexture", "Image not found");
    return NULL;
  }
  
  void MediaServer::handleImageAdded(string& path) {
    /*
    cout << "onImageAdded: " << path << endl;
    cout << "numImages: " << getNumImages() << endl;
    */
    ofNotifyEvent(onImageAdded, path, this);
  }
  void MediaServer::handleImageRemoved(string& path) {
    /*
    cout << "onImageRemoved: " << path << endl;
    cout << "numImages: " << getNumImages() << endl;
    */
    ofNotifyEvent(onImageRemoved, path, this);
  }
 
  void MediaServer::handleVideoAdded(string& path) {
    //cout << "onVideoAdded: " << path << endl;
    ofNotifyEvent(onVideoAdded, path, this);
  }
  void MediaServer::handleVideoRemoved(string& path) {
    //cout << "onVideoRemoved: " << path << endl;
    ofNotifyEvent(onVideoRemoved, path, this);
  }
  
  void MediaServer::addWatcherListeners() {
    ofAddListener(imageWatcher.onItemAdded, this, &MediaServer::handleImageAdded);
    ofAddListener(imageWatcher.onItemRemoved, this, &MediaServer::handleImageRemoved);
    ofAddListener(videoWatcher.onItemAdded, this, &MediaServer::handleVideoAdded);
    ofAddListener(videoWatcher.onItemRemoved, this, &MediaServer::handleVideoRemoved);
  }
  
  void MediaServer::removeWatcherListeners() {
    ofRemoveListener(imageWatcher.onItemAdded, this, &MediaServer::handleImageAdded);
    ofRemoveListener(imageWatcher.onItemRemoved, this, &MediaServer::handleImageRemoved);
    ofRemoveListener(videoWatcher.onItemAdded, this, &MediaServer::handleVideoAdded);
    ofRemoveListener(videoWatcher.onItemRemoved, this, &MediaServer::handleVideoRemoved);
  }
  
} // namespace piMapper
} // namespace ofx