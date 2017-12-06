#pragma once

#include "ofMain.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

class DirectoryWatcher : public ofThread {
	public:
		DirectoryWatcher(string path, int watcherMediaType);
		virtual ~DirectoryWatcher();
		vector<string> & getFilePaths();
		int getMediaType();

		void beginWatch(int intervalInMillis = 5000);
		void endWatch();
		void threadedFunction();

		/**
		 * Triggered when the file count of a directory increases
		 * or decreases.
		 *
		 * Sender is a pointer to this DirectoryWatcher
		 */
		ofEvent<void> directoryFileCountChangedEvent;
	private:
		ofDirectory _directory;
		vector<string> _filePaths;
		std::string directoryPath;
		int _mediaType;

		int dirSize;
		long watchInterval; // in millis.
};

} // namespace piMapper
} // namespace ofx