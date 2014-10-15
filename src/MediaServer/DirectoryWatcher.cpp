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
        filter = new VideoPathFilter();
      } else {
        filter = new ImagePathFilter();
      }
      dirWatcher.registerAllEvents(this);
      
      // For some reason the filters are not working,
      // we leave just the path here and do the filter logic in the listeners
      dirWatcher.addPath(path);
      
      // Initial directory listing. Fill the file paths vector.
      IO::DirectoryUtils::list(path, filePaths, true, filter);
    }
    
    DirectoryWatcher::~DirectoryWatcher() {
      delete filter;
      filter = NULL;
    }
    
    std::vector<std::string>& DirectoryWatcher::getFilePaths() {
      return filePaths;
    }
    
  } // namespace piMapper
} // namespace ofx