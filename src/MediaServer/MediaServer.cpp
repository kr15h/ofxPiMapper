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