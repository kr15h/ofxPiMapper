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

DirectoryWatcher::DirectoryWatcher(std::string path, int watcherMediaType){
	mediaType = watcherMediaType;
	// Decide what filter we need depending on media type
	if(mediaType == SourceType::SOURCE_TYPE_VIDEO){
		filter = new VideoPathFilter();
	}else if(mediaType == SourceType::SOURCE_TYPE_IMAGE){
		filter = new ImagePathFilter();
	}else{
		ofLogFatalError("DirectoryWatcher::DirectoryWatcher", "Unkonwn media type");
		std::exit(EXIT_FAILURE);
	}
	dirWatcher.registerAllEvents(this);
	// For some reason the filters are not working,
	// we leave just the path here and do the filter logic in the listeners
	dirWatcher.addPath(path);
	// Initial directory listing. Fill the file paths vector.
	IO::DirectoryUtils::list(path, filePaths, true, filter);
}

DirectoryWatcher::~DirectoryWatcher(){
	delete filter;
	filter = NULL;
}

std::vector <std::string> & DirectoryWatcher::getFilePaths(){
	return filePaths;
}

int DirectoryWatcher::getMediaType(){
	return mediaType;
}

} // namespace piMapper
} // namespace ofx