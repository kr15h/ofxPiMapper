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
  videoWatcher(ofToDataPath(DEFAULT_VIDEOS_DIR, true), SourceType::SOURCE_TYPE_VIDEO),
  imageWatcher(ofToDataPath(DEFAULT_IMAGES_DIR, true), SourceType::SOURCE_TYPE_IMAGE) {
    addWatcherListeners();
  }

  MediaServer::~MediaServer() {
    cout << "Media server is over" << endl;
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
  
  BaseSource* MediaServer::loadMedia(string &path, int mediaType) {
    // Chose load method depending on type
    if (mediaType == SourceType::SOURCE_TYPE_IMAGE) {
      return loadImage(path);
    } else if (mediaType == SourceType::SOURCE_TYPE_VIDEO) {
      return loadVideo(path);
    } else {
      std::stringstream ss;
      ss << "Can not load media of unknown type: " << mediaType;
      ofLogFatalError("MediaServer") << ss.str();
      std::exit(EXIT_FAILURE);
    }
    return NULL;
  }
  
  BaseSource* MediaServer::loadImage(string& path) {
    ImageSource* imageSource = NULL;
    // Check if this image is already loaded
    bool isImageLoaded = false;
    if (loadedSources.count(path)) {
      imageSource = static_cast<ImageSource*>(loadedSources[path]);
      isImageLoaded = true;
    }
    // If image is loaded
    if (isImageLoaded) {
      // Increase reference count of this source
      //referenceCount[path]++;
      imageSource->referenceCount++;
      std::stringstream refss;
      refss << "Current reference count for " << path << " = " << imageSource->referenceCount;
      ofLogNotice("MediaServer") << refss.str();
      // Notify objects registered to onImageLoaded event
      std::stringstream ss;
      ss << "Image " << path << " already loaded";
      ofLogNotice("MediaServer") << ss.str();
      ofNotifyEvent(onImageLoaded, path, this);
      return imageSource;
    }
    // Else load fresh
    imageSource = new ImageSource();
    imageSource->loadImage(path);
    loadedSources[path] = imageSource;
    // Set reference count of this image path to 1
    //referenceCount[path] = 1;
    std::stringstream refss;
    refss << "Initialized reference count of " << path << " to " << imageSource->referenceCount;
    ofLogNotice("MediaServer") << refss.str();
    // Notify objects registered to onImageLoaded event
    ofNotifyEvent(onImageLoaded, path, this);
    return imageSource;
  }
  
  void MediaServer::unloadImage(string& path) {
    
    ImageSource* source = static_cast<ImageSource*>(getSourceByPath(path));
    // Decrease reference count of the image
    //referenceCount[path]--;
    source->referenceCount--;
    // Unload only if reference count is less or equal to 0
    cout << "referenceCount: " << source->referenceCount << endl;
    if (source->referenceCount > 0) {
      ofLogNotice("MediaServer") << "Not unloading image as it is being referenced elsewhere";
      return;
    }
    // Reference count 0 or less, unload image
    std::stringstream ss;
    ss << "Removing image " << path;
    ofLogNotice("MediaServer") << ss.str();
    // Destroy image source
    if (loadedSources.count(path)) {
      //loadedSources[path]->clear();
      delete loadedSources[path];
      loadedSources.erase(path);
      ofNotifyEvent(onImageUnloaded, path, this);
      return;
    }
    // Something wrong here, we should be out of the routine by now
    std::stringstream failss;
    failss << "Failed to remove image source: " << path;
    ofLogFatalError("MediaServer") << failss.str();
    std::exit(EXIT_FAILURE);
  }
  
  BaseSource* MediaServer::loadVideo(string& path) {
    cout << "loading video: " << path << endl;
    VideoSource* videoSource = NULL;
    // Check if this video is already loaded
    bool isVideoLoaded = false;
    if (loadedSources.count(path)) {
      videoSource = static_cast<VideoSource*>(loadedSources[path]);
      isVideoLoaded = true;
    }
    // If is loaded
    if (isVideoLoaded) {
      // Increase reference count of this source
      //referenceCount[path]++;
      videoSource->referenceCount++;
      std::stringstream refss;
      refss << "Current reference count for " << path << " = " << videoSource->referenceCount;
      ofLogNotice("MediaServer") << refss.str();
      // Notify objects registered to onImageLoaded event
      std::stringstream ss;
      ss << "Video " << path << " already loaded";
      ofLogNotice("MediaServer") << ss.str();
      ofNotifyEvent(onVideoLoaded, path, this);
      return videoSource;
    }
    // Else load fresh
    videoSource = new VideoSource();
    videoSource->loadVideo(path);
    loadedSources[path] = videoSource;
    // Set reference count of this image path to 1
    //referenceCount[path] = 1;
    std::stringstream refss;
    refss << "Initialized reference count of " << path << " to " << videoSource->referenceCount;
    ofLogNotice("MediaServer") << refss.str();
    ofNotifyEvent(onVideoLoaded, path, this);
    return videoSource;
  }
  
  void MediaServer::unloadVideo(string& path) {
    VideoSource* videoSource = static_cast<VideoSource*>(getSourceByPath(path));
    // Decrease reference count of the video
    //referenceCount[path]--;
    videoSource->referenceCount--;
    // Unload only if reference count is less or equal to 0
    if (videoSource->referenceCount > 0) {
      ofLogNotice("MediaServer") << "Not unloading video as it is being referenced elsewhere";
      return;
    }
    // Reference count 0 or less, let's unload the video
    std::stringstream ss;
    ss << "Removing video " << path;
    ofLogNotice("MediaServer") << ss.str();
    // Distroy video source
    if (loadedSources.count(path)) {
      loadedSources[path]->clear();
      delete loadedSources[path];
      loadedSources.erase(path);
      ofNotifyEvent(onVideoUnloaded, path, this);
      return;
    }
    // Something wrong here, we should be out of the routine by now
    std::stringstream failss;
    failss << "Failed to remove video source: " << path;
    ofLogFatalError("MediaServer") << failss.str();
    std::exit(EXIT_FAILURE);
  }
  
  void MediaServer::unloadMedia(string &path) {
    if (loadedSources.count(path)) {
      BaseSource* mediaSource = getSourceByPath(path);
      if (mediaSource->getType() == SourceType::SOURCE_TYPE_IMAGE) {
        unloadImage(path);
      } else if (mediaSource->getType() == SourceType::SOURCE_TYPE_VIDEO) {
        unloadVideo(path);
      } else {
        // Oh my god, what to do!? Relax and exit.
        ofLogFatalError("MediaServer") << "Attempt to unload media of unknown type";
        std::exit(EXIT_FAILURE);
      }
    } else {
      std:stringstream ss;
      ss << "Media with path " << path << " is not loaded and thus can't be unloaded";
      ofLogFatalError("MediaServer") << ss.str();
      std::exit(EXIT_FAILURE);
    }
  }
  
  // Clear all loaded media
  void MediaServer::clear() {
    typedef std::map<std::string, BaseSource*>::iterator it_type;
    for (it_type i = loadedSources.begin(); i != loadedSources.end(); i++) {
      delete i->second;
    }
    loadedSources.clear();
  }
  
  BaseSource* MediaServer::getSourceByPath(std::string& mediaPath) {
    cout << "num loaded sources: " << loadedSources.size() << endl;
    if (loadedSources.count(mediaPath)) {
      return loadedSources[mediaPath];
    }
    // Source not found, exit with error
    std::stringstream ss;
    ss << "Could not find source by path: " << mediaPath;
    ofLogFatalError("MediaServer") << ss.str();
    std::exit(EXIT_FAILURE);
  }
  
  std::string MediaServer::getDefaultImageDir() {
    return DEFAULT_IMAGES_DIR;
  }
  
  std::string MediaServer::getDefaultVideoDir() {
    return DEFAULT_VIDEOS_DIR;
  }
  
  std::string MediaServer::getDefaultMediaDir(int sourceType) {
    if (sourceType == SourceType::SOURCE_TYPE_IMAGE) {
      return getDefaultImageDir();
    } else if (sourceType == SourceType::SOURCE_TYPE_VIDEO) {
      return getDefaultVideoDir();
    } else {
      std::stringstream ss;
      ss << "Could not get default media dir. Unknown source type: " << sourceType;
      ofLogFatalError("MediaServer") << ss.str();
      std::exit(EXIT_FAILURE);
    }
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