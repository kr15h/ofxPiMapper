//
//  DirectoryWatcher.cpp
//  example
//
//  Created by felix on 23.09.14.
//
//

#include "DirectoryWatcher.h"

namespace ofx {
namespace piMapper {
DirectoryWatcher::DirectoryWatcher(std::string path, bool video) {
  if (video) {
    filter = CustomVideoPathFilter();
  } else {
    filter = CustomImagePathFilter();
  }
  dirWatcher.registerAllEvents(this);
  dirWatcher.addPath(path, true, &filter);
}
}
}