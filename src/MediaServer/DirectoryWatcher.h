#pragma once

#include "ofMain.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

class DirectoryWatcher {
	public:
		DirectoryWatcher(string path, int watcherMediaType);
		vector<string> & getFilePaths();
		int getMediaType();

	private:
		ofDirectory _directory;
		vector<string> _filePaths;
		int _mediaType;
};

} // namespace piMapper
} // namespace ofx