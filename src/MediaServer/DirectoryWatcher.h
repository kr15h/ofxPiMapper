//
//  DirectoryWatcher.h
//  example
//
//  Created by felix on 23.09.14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxIO.h"

namespace ofx {
namespace piMapper {

class CustomPathFilter : public ofx::IO::AbstractPathFilter {
 public:
  CustomPathFilter() {};
  virtual ~CustomPathFilter() {};
  virtual bool accept(const Poco::Path& path) const {};
};

class CustomVideoPathFilter : public CustomPathFilter {
 public:
  CustomVideoPathFilter() {};
  virtual ~CustomVideoPathFilter() {};
  // TODO: Find useful filters e.g. *.mp4, etc
  bool accept(const Poco::Path& path) const {
    return !Poco::File(path).isHidden() &&
           ofIsStringInString(path.toString(), "mp4");
  }
};

class CustomImagePathFilter : public CustomPathFilter {
 public:
  CustomImagePathFilter() {};
  virtual ~CustomImagePathFilter() {};
  // TODO: Find useful filters e.g. *.png,*.jpeg, etc.
  bool accept(const Poco::Path& path) const {
    return !Poco::File(path).isHidden() &&
           ofIsStringInString(path.toString(), "png");
  }
};

class DirectoryWatcher {
 public:
  DirectoryWatcher(std::string path, bool video);

  // TODO make useful stuff with onDirectoryWatcher*
  void onDirectoryWatcherItemAdded(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    string path = evt.item.path();
    filePaths.push_back(path);
    ofNotifyEvent(onItemAdded, path, this);
  }

  void onDirectoryWatcherItemRemoved(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    string path = evt.item.path();
    
    // TODO Remove items from Vector
    
    ofNotifyEvent(onItemRemoved, path, this);
  }

  void onDirectoryWatcherItemModified(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    string path = evt.item.path();
    
    ofNotifyEvent(onItemModified, path, this);
  }

  void onDirectoryWatcherItemMovedFrom(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    string path = evt.item.path();
    ofLogNotice("ofApp::onDirectoryWatcherItemMovedFrom")
        << "Moved From: " << path;
    ofNotifyEvent(onItemMovedFrom, path, this);
  }

  void onDirectoryWatcherItemMovedTo(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    string path = evt.item.path();
    ofLogNotice("ofApp::onDirectoryWatcherItemMovedTo")
        << "Moved To: " << path;
    ofNotifyEvent(onItemMovedTo, path, this);
  }

  void onDirectoryWatcherError(const Poco::Exception& exc) {
    ofLogError("ofApp::onDirectoryWatcherError")
        << "Error: " << exc.displayText();
  }

  std::vector<std::string> filePaths;
  
  // Custom events
  ofEvent<string> onItemAdded;
  ofEvent<string> onItemRemoved;
  ofEvent<string> onItemModified;
  ofEvent<string> onItemMovedFrom;
  ofEvent<string> onItemMovedTo;

 private:
  ofx::IO::DirectoryWatcherManager dirWatcher;
  CustomPathFilter filter;
};
}
}