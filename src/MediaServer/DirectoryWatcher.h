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
    ofSendMessage("Added:    " + evt.item.path());
    filePaths.push_back(evt.item.path());
  }

  void onDirectoryWatcherItemRemoved(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    ofSendMessage("Removed:  " + evt.item.path());
    // TODO Remove items from Vector
  }

  void onDirectoryWatcherItemModified(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    ofSendMessage("Modified: " + evt.item.path());
  }

  void onDirectoryWatcherItemMovedFrom(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    ofLogNotice("ofApp::onDirectoryWatcherItemMovedFrom")
        << "Moved From: " << evt.item.path();
  }

  void onDirectoryWatcherItemMovedTo(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    ofLogNotice("ofApp::onDirectoryWatcherItemMovedTo")
        << "Moved To: " << evt.item.path();
  }

  void onDirectoryWatcherError(const Poco::Exception& exc) {
    ofLogError("ofApp::onDirectoryWatcherError")
        << "Error: " << exc.displayText();
  }

  std::vector<std::string> filePaths;

 private:
  ofx::IO::DirectoryWatcherManager dirWatcher;
  CustomPathFilter filter;
};
}
}