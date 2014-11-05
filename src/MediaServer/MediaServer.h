//
//  MediaServer.h
//  example
//
//  Created by felix on 13.09.14.
//
//

// TODO: move reference counting, enabling and disabling of sources
//       to source classes themselves

#pragma once

#include "ofMain.h"
#include "DirectoryWatcher.h"
#include "BaseSource.h"
#include "ImageSource.h"
#include "VideoSource.h"
#include "FboSource.h"
#include "SourceType.h"

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
  int getNumFboSources(); // new
  std::vector<std::string>& getVideoPaths();
  std::vector<std::string>  getVideoNames();
  std::vector<std::string>& getImagePaths();
  std::vector<std::string>  getImageNames();
  std::vector<std::string>  getFboSourceNames(); // new
  
  BaseSource* loadMedia(string& path, int mediaType);
  BaseSource* loadImage(string& path);
  void unloadImage(string& path);
  BaseSource* loadVideo(string& path);
  void unloadVideo(string& path);
  void unloadMedia(string& path);
  void clear(); // Force all loaded source unload
  BaseSource* getSourceByPath(std::string& mediaPath);
  std::string getDefaultImageDir();
  std::string getDefaultVideoDir();
  std::string getDefaultMediaDir(int sourceType);
  
  // Do things with FBO sources
  void addFboSource(FboSource& fboSource);
  BaseSource* loadFboSource(std::string& fboSourceName);
  void unloadFboSource(std::string& fboSourceName);
  
  // Custom events, add/remove
  ofEvent<std::string> onImageAdded;
  ofEvent<std::string> onImageRemoved;
  ofEvent<std::string> onVideoAdded;
  ofEvent<std::string> onVideoRemoved;
  ofEvent<std::string> onFboSourceAdded;
  ofEvent<std::string> onFboSourceRemoved;
  // load/unload
  ofEvent<std::string> onImageLoaded;
  ofEvent<std::string> onImageUnloaded;
  ofEvent<std::string> onVideoLoaded;
  ofEvent<std::string> onVideoUnloaded;
  ofEvent<std::string> onFboSourceLoaded;
  ofEvent<std::string> onFboSourceUnloaded;

 private:
  // Directory Watchers
  ofx::piMapper::DirectoryWatcher videoWatcher;
  ofx::piMapper::DirectoryWatcher imageWatcher;
  std::map<std::string, BaseSource*> loadedSources;
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
  
  // FBO source storage before they go to loadedSources
  std::vector<FboSource*> fboSources; // FBO source storage
};
} // namespace piMapper
} // namespace ofx
