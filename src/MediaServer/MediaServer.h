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

 private:
  // Video
  ofx::piMapper::DirectoryWatcher videoWatcher;
  // Images
  ofx::piMapper::DirectoryWatcher imageWatcher;
};
}
}
