//
//  MediaServer.h
//  example
//
//  Created by felix on 13.09.14.
//
//

// TODO: move reference counting, enabling and disabling of sources
//       to source classes themselves

#pragma once

#include "ofMain.h"
#include "DirectoryWatcher.h"

/* Discussion: This could be the right place for a Factory Method or
 * Abstract Factory design pattern - replace all these includes with a
 * SourceFactory that can create sources with the interfaces below. */
#include "BaseSource.h"
#include "ImageSource.h"
#include "VideoSource.h"
#include "FboSource.h"
#include "SourceType.h"

#define DEFAULT_IMAGES_DIR "sources/images/"
#define DEFAULT_VIDEOS_DIR "sources/videos/"

#define PI_IMAGES_DIR "/boot/ofxpimapper/sources/images"
#define PI_VIDEOS_DIR "/boot/ofxpimapper/sources/videos"

namespace ofx {
namespace piMapper {

class MediaServer {
	public:
		MediaServer();
		virtual ~MediaServer();

		int getNumVideos();
		int getNumImages();
		int getNumFboSources(); // new
		vector <string> & getVideoPaths();
		vector <string>  getVideoNames();
		vector <string> & getImagePaths();
		vector <string>  getImageNames();
		vector <string>  getFboSourceNames(); // new

		BaseSource * loadMedia(string & path, int mediaType);
		BaseSource * loadImage(string & path);
		void unloadImage(string & path);
		BaseSource * loadVideo(string & path);
		void unloadVideo(string & path);
		void unloadMedia(string & path);
		void clear(); // Force all loaded source unload
		BaseSource * getSourceByPath(string & mediaPath);
		string getDefaultImageDir();
		string getDefaultVideoDir();
		string getDefaultMediaDir(int sourceType);

		// Do things with FBO sources
		void addFboSource(FboSource & fboSource); // could be called also as register FBO source
		BaseSource * loadFboSource(string & fboSourceName);
		void unloadFboSource(string & fboSourceName);

		// Custom events, add/remove
		ofEvent <string> onImageAdded;
		ofEvent <string> onImageRemoved;
		ofEvent <string> onVideoAdded;
		ofEvent <string> onVideoRemoved;
		ofEvent <string> onFboSourceAdded;
		ofEvent <string> onFboSourceRemoved;
		// load/unload
		ofEvent <string> onImageLoaded;
		ofEvent <string> onImageUnloaded;
		ofEvent <string> onVideoLoaded;
		ofEvent <string> onVideoUnloaded;
		ofEvent <string> onFboSourceLoaded;
		ofEvent <string> onFboSourceUnloaded;

	private:
		// Directory Watchers
		ofx::piMapper::DirectoryWatcher videoWatcher;
		ofx::piMapper::DirectoryWatcher imageWatcher;
    
        ofx::piMapper::DirectoryWatcher piVideoWatcher;
        ofx::piMapper::DirectoryWatcher piImageWatcher;
        vector <string> _tempImagePaths;
        vector <string> _tempVideoPaths;
    
		map <string, BaseSource *> loadedSources;
		// imageWatcher event listeners
		void handleImageAdded(string & path);
		void handleImageRemoved(string & path);
		// TODO rest of listeners
		/*
		void onImageModified();
		void onImageMovedFrom();
		void onImageMovedTo();
		*/

		// videoWatcher event listeners
		void handleVideoAdded(string & path);
		void handleVideoRemoved(string & path);
		// TODO rest of listeners
		/*
		 void onVideoModified();
		 void onVideoMovedFrom();
		 void onVideoMovedTo();
		 */

		// Add/remove event listeners.
		// Add event listeners to image and video watcher events.
		void addWatcherListeners();

		// Remove event listeners to image and video watcher events
		void removeWatcherListeners();

		// FBO source storage before they go to loadedSources
		vector <FboSource *> fboSources; // FBO source storage
};

} // namespace piMapper
} // namespace ofx
