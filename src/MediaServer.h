//
//  MediaServer.h
//  example
//
//  Created by felix on 13.09.14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxIO.h"

#define DEFAULT_IMAGES_DIR "sources/images/"
#define DEFAULT_VIDEOS_DIR "sources/videos/"

namespace ofx {
namespace piMapper {

class CustomVideoPathFilter : public ofx::IO::AbstractPathFilter {
  CustomVideoPathFilter() {};
  virtual ~CustomVideoPathFilter() {};
  // TODO: Find useful filters e.g. *.mp4, etc
  bool const accept(Poco::Path& path) const {
    return !Poco::File(path).isHidden() &&
           ofIsStringInString(path.toString(), "mp4");
  }
};

class CustomImagePathFilter : public ofx::IO::AbstractPathFilter {
  CustomImagePathFilter() {};
  virtual ~CustomImagePathFilter() {};
  // TODO: Find useful filters e.g. *.png,*.jpeg, etc.
  bool const accept(Poco::Path& path) const {
    return !Poco::File(path).isHidden() &&
           ofIsStringInString(path.toString(), "png");
  }
};
class MediaServer {
 public:
  MediaServer();

  // TODO make useful stuff with onDirectoryWatcher*
  void onDirectoryWatcherItemAdded(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    ofSendMessage("Added:    " + evt.item.path());
  }

  void onDirectoryWatcherItemRemoved(
      const ofx::IO::DirectoryWatcherManager::DirectoryEvent& evt) {
    ofSendMessage("Removed:  " + evt.item.path());
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

 private:
  // Video
  ofx::IO::DirectoryWatcherManager videoWatcher;
  ofx::IO::HiddenFileFilter videoFileFilter;

  // Images
  ofx::IO::DirectoryWatcherManager imageWatcher;
  ofx::IO::HiddenFileFilter imageFileFilter;
};
}
}
