#include "DirectoryWatcher.h"

namespace ofx {
namespace piMapper {

DirectoryWatcher::DirectoryWatcher(std::string path, int watcherMediaType){
	directoryPath = path;
	_mediaType = watcherMediaType;

	if(_mediaType == SourceType::SOURCE_TYPE_VIDEO){
		_directory.allowExt("mp4");
		_directory.allowExt("h264");
		_directory.allowExt("mov");
		_directory.allowExt("avi");
		_directory.allowExt("ogv");
		_directory.allowExt("mpeg");
	}else if(_mediaType == SourceType::SOURCE_TYPE_IMAGE){
		_directory.allowExt("png");
		_directory.allowExt("jpg");
		_directory.allowExt("jpeg");
	}else{
		ofLogFatalError("DirectoryWatcher::DirectoryWatcher", "Unkonwn media type");
		exit(EXIT_FAILURE);
	}

	_directory.listDir(directoryPath);
	_directory.sort();

	for(int i = 0; i < _directory.size(); ++i){
		_filePaths.push_back(directoryPath + _directory.getName(i));

		ofFile file(directoryPath + _directory.getName(i));
		if(_mediaType == SourceType::SOURCE_TYPE_VIDEO){
			file.copyTo("sources/videos/" + _directory.getName(i));
		}else if(_mediaType == SourceType::SOURCE_TYPE_IMAGE){
			file.copyTo("sources/images/" + _directory.getName(i));
		}
	}

	dirSize = _directory.size();
}

DirectoryWatcher::~DirectoryWatcher() {
	if(isThreadRunning()){
		stopThread();
	}
}

std::vector<std::string> & DirectoryWatcher::getFilePaths(){
	return _filePaths;
}

int DirectoryWatcher::getMediaType(){
	return _mediaType;
}

void DirectoryWatcher::beginWatch(int intervalInMillis) {
	watchInterval = intervalInMillis;
	startThread();
}

void DirectoryWatcher::threadedFunction() {

	while (isThreadRunning()) {

		int newSize = _directory.listDir();
		if (newSize > dirSize) {
			ofLogVerbose("DirectoryWatcher") << "Directory changed";
			dirSize = newSize;
			ofNotifyEvent(directoryFileAddedEvent, this);
		} else if (newSize < dirSize) {
			dirSize = newSize;
			ofNotifyEvent(directoryFileRemovedEvent, this);
		}



		sleep(watchInterval);
	}
}

} // namespace piMapper
} // namespace ofx
