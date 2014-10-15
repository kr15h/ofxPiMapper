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

MediaServer::MediaServer()
    : videoWatcher(ofToDataPath(DEFAULT_VIDEOS_DIR, true), true),
      imageWatcher(ofToDataPath(DEFAULT_IMAGES_DIR, true), false) {}

MediaServer::~MediaServer() {};

int MediaServer::getNumImages() { return imageWatcher.getFilePaths().size(); }
int MediaServer::getNumVideos() { return videoWatcher.getFilePaths().size(); }

std::vector<std::string>& MediaServer::getImagePaths() {
  return imageWatcher.getFilePaths();
}
std::vector<std::string>& MediaServer::getVideoPaths() {
  return videoWatcher.getFilePaths();
}
}
}