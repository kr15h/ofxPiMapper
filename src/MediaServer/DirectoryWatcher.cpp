#include "DirectoryWatcher.h"

namespace ofx {
namespace piMapper {

DirectoryWatcher::DirectoryWatcher(string path, int watcherMediaType){
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
	
	_directory.listDir(path);
	_directory.sort();
	
	for(int i = 0; i < _directory.size(); ++i){
		_filePaths.push_back(path + _directory.getName(i));
		
		ofFile file(path + _directory.getName(i));
		if(_mediaType == SourceType::SOURCE_TYPE_VIDEO){
			file.copyTo("sources/videos/" + _directory.getName(i));
		}else if(_mediaType == SourceType::SOURCE_TYPE_IMAGE){
			file.copyTo("sources/images/" + _directory.getName(i));
		}
	}
}

vector <string> & DirectoryWatcher::getFilePaths(){
	return _filePaths;
}

int DirectoryWatcher::getMediaType(){
	return _mediaType;
}

} // namespace piMapper
} // namespace ofx
