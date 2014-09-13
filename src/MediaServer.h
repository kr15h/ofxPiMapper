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
class MediaServer {
 public:
  MediaServer();

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
