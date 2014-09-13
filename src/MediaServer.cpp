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
MediaServer::MediaServer() {
  videoWatcher.registerAllEvents(this);
  videoWatcher.addPath(ofToDataPath(DEFAULT_VIDEOS_DIR, true), true,
                       &videoFileFilter);
  imageWatcher.registerAllEvents(this);
  imageWatcher.addPath(ofToDataPath(DEFAULT_IMAGES_DIR, true), true,
                       &imageFileFilter);
}
}
}