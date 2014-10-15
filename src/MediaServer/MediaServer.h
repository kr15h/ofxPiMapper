//
//  MediaServer.h
//  example
//
//  Created by felix on 13.09.14.
//
//

#pragma once

#include "ofMain.h"
#include "DirectoryWatcher.h"

#define DEFAULT_IMAGES_DIR "sources/images/"
#define DEFAULT_VIDEOS_DIR "sources/videos/"

namespace ofx {
namespace piMapper {

class MediaServer {
 public:
  MediaServer();
  virtual ~MediaServer();

  int getNumVideos();
  int getNumImages();
  std::vector<string>& getVideoPaths();
  std::vector<string>& getImagePaths();
  
  // Custom events
  //ofEvent<string> on

 private:
  // Directory Watchers
  ofx::piMapper::DirectoryWatcher videoWatcher;
  ofx::piMapper::DirectoryWatcher imageWatcher;
   
  // imageWatcher event listeners
  void onImageAdded(string& path);
  void onImageRemoved(string& path);
  // TODO rest of listeners
  /*
  void onImageModified();
  void onImageMovedFrom();
  void onImageMovedTo();
  */
  
  // videoWatcher event listeners
  void onVideoAdded(string& path);
  void onVideoRemoved(string& path);
  // TODO rest of listeners
  /*
   void onVideoModified();
   void onVideoMovedFrom();
   void onVideoMovedTo();
   */
   
  // Add/remove event listeners.
  // Add event listeners to image and video watcher events.
  void addWatcherListeners();
  
  // Remove event listeners to image and video watcher events
  void removeWatcherListeners();
};
} // namespace piMapper
} // namespace ofx
