//
//  DirectoryWatcher.h
//  example
//
//  Created by felix on 23.09.14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxIO.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

class BasePathFilter : public ofx::IO::AbstractPathFilter {
	public:
		BasePathFilter(){}
		virtual ~BasePathFilter(){}
		virtual bool accept(const Poco::Path & path) const { return false; }
};

class VideoPathFilter : public BasePathFilter {
	public:
		VideoPathFilter(){}
		virtual ~VideoPathFilter(){}

		// TODO: Make Raspi load only mp4s (and mov and h264?)
		//       How to detect codec? Read file headers?

		bool accept(const Poco::Path & path) const {
			return !Poco::File(path).isHidden() &&
				   (ofIsStringInString(path.toString(), ".mp4") ||
					ofIsStringInString(path.toString(), ".h264") ||
					ofIsStringInString(path.toString(), ".mov") ||
					ofIsStringInString(path.toString(), ".avi") ||
					ofIsStringInString(path.toString(), ".ogv") ||
					ofIsStringInString(path.toString(), ".mpeg"));
		}
};

class ImagePathFilter : public BasePathFilter {
	public:
		ImagePathFilter(){}
		virtual ~ImagePathFilter(){}

		bool accept(const Poco::Path & path) const {
			return !Poco::File(path).isHidden() &&
				   (ofIsStringInString(path.toString(), ".png") ||
					ofIsStringInString(path.toString(), ".jpg") ||
					ofIsStringInString(path.toString(), ".jpeg"));
		}
};

class DirectoryWatcher {
	public:
		DirectoryWatcher(string path, int watcherMediaType);
		~DirectoryWatcher();

		// TODO make useful stuff with onDirectoryWatcher*
		void onDirectoryWatcherItemAdded(const ofx::IO::DirectoryWatcherManager::DirectoryEvent & evt){
			string path = evt.item.path();
			Poco::Path pocoPath = Poco::Path(path);
			if(!filter->accept(pocoPath)){
				return;
			}
			filePaths.push_back(path);
			ofNotifyEvent(onItemAdded, path, this);
		}

		void onDirectoryWatcherItemRemoved(const ofx::IO::DirectoryWatcherManager::DirectoryEvent & evt){
			string path = evt.item.path();
			Poco::Path pocoPath = Poco::Path(path);
			if(!filter->accept(pocoPath)){
				return;
			}
			// Remove path from vector
			for(int i = 0; i < filePaths.size(); i++){
				if(path == filePaths[i]){
					filePaths.erase(filePaths.begin() + i);
					break;
				}
			}
			ofNotifyEvent(onItemRemoved, path, this);
		}

		void onDirectoryWatcherItemModified(const ofx::IO::DirectoryWatcherManager::DirectoryEvent & evt){
			string path = evt.item.path();
			Poco::Path pocoPath = Poco::Path(path);
			if(!filter->accept(pocoPath)){
				return;
			}
			ofNotifyEvent(onItemModified, path, this);
		}

		void onDirectoryWatcherItemMovedFrom(const ofx::IO::DirectoryWatcherManager::DirectoryEvent & evt){
			string path = evt.item.path();
			Poco::Path pocoPath = Poco::Path(path);
			if(!filter->accept(pocoPath)){
				return;
			}
			ofLogNotice("ofApp::onDirectoryWatcherItemMovedFrom")
				<< "Moved From: " << path;
			ofNotifyEvent(onItemMovedFrom, path, this);
		}

		void onDirectoryWatcherItemMovedTo(const ofx::IO::DirectoryWatcherManager::DirectoryEvent & evt){
			string path = evt.item.path();
			Poco::Path pocoPath = Poco::Path(path);
			if(!filter->accept(pocoPath)){
				return;
			}
			ofLogNotice("ofApp::onDirectoryWatcherItemMovedTo")
				<< "Moved To: " << path;
			ofNotifyEvent(onItemMovedTo, path, this);
		}

		void onDirectoryWatcherError(const Poco::Exception & exc){
			ofLogError("ofApp::onDirectoryWatcherError")
				<< "Error: " << exc.displayText();
		}

		// Getters
		vector <string> & getFilePaths();
		int getMediaType();

		// Custom events
		ofEvent <string> onItemAdded;
		ofEvent <string> onItemRemoved;
		ofEvent <string> onItemModified;
		ofEvent <string> onItemMovedFrom;
		ofEvent <string> onItemMovedTo;

	private:
		ofx::IO::DirectoryWatcherManager dirWatcher;
		BasePathFilter * filter;
		vector <string> filePaths;
		int mediaType;
};

} // namespace piMapper
} // namespace ofx