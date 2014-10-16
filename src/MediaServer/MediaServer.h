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
#include "MediaType.h"

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
  std::vector<string> getImageNames();
  
  // Image loading and handling
  void loadImage(string& path);
  void unloadImage(string& path);
  ofTexture* getImageTexture(string& path);
  
  // Custom events
  ofEvent<string> onImageAdded;
  ofEvent<string> onImageRemoved;
  ofEvent<string> onVideoAdded;
  ofEvent<string> onVideoRemoved;
  ofEvent<string> onImageLoaded;
  ofEvent<string> onImageUnloaded;

 private:
  // Directory Watchers
  ofx::piMapper::DirectoryWatcher videoWatcher;
  ofx::piMapper::DirectoryWatcher imageWatcher;
  
  // Loaded media
  vector<ofImage> loadedImages;
  vector<string> loadedImagePaths;
   
  // imageWatcher event listeners
  void handleImageAdded(string& path);
  void handleImageRemoved(string& path);
  // TODO rest of listeners
  /*
  void onImageModified();
  void onImageMovedFrom();
  void onImageMovedTo();
  */
  
  // videoWatcher event listeners
  void handleVideoAdded(string& path);
  void handleVideoRemoved(string& path);
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
