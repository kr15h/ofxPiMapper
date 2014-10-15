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
  
  void MediaServer::onImageAdded(string& path) {
    cout << "onImageAdded: " << path << endl;
  }
  void MediaServer::onImageRemoved(string& path) {
    cout << "onImageRemoved: " << path << endl;
  }
 
  void MediaServer::onVideoAdded(string& path) {
    cout << "onVideoAdded: " << path << endl;
  }
  void MediaServer::onVideoRemoved(string& path) {
    cout << "onVideoRemoved: " << path << endl;
  }
  
  void MediaServer::addWatcherListeners() {
    ofAddListener(imageWatcher.onItemAdded, this, &MediaServer::onImageAdded);
    ofAddListener(imageWatcher.onItemRemoved, this, &MediaServer::onImageRemoved);
    ofAddListener(videoWatcher.onItemAdded, this, &MediaServer::onVideoAdded);
    ofAddListener(videoWatcher.onItemRemoved, this, &MediaServer::onVideoRemoved);
  }
  
  void MediaServer::removeWatcherListeners() {
    ofRemoveListener(imageWatcher.onItemAdded, this, &MediaServer::onImageAdded);
    ofRemoveListener(imageWatcher.onItemRemoved, this, &MediaServer::onImageRemoved);
    ofRemoveListener(videoWatcher.onItemAdded, this, &MediaServer::onVideoAdded);
    ofRemoveListener(videoWatcher.onItemRemoved, this, &MediaServer::onVideoRemoved);
  }
  
} // namespace piMapper
} // namespace ofx