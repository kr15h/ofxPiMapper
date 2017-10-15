#pragma once

#include "ofMain.h"
#include "DirectoryWatcher.h"

#include "BaseSource.h"
#include "ImageSource.h"
#include "VideoSource.h"
#include "FboSource.h"
#include "SourceType.h"

#define DEFAULT_IMAGES_DIR "sources/images/"
#define DEFAULT_VIDEOS_DIR "sources/videos/"

#define PI_IMAGES_DIR "/boot/ofxpimapper/sources/images/"
#define PI_VIDEOS_DIR "/boot/ofxpimapper/sources/videos/"

/* 
 * These you can get when you apt-get install usbmount
 */
#define USB0_IMAGES_DIR "/media/usb0/"
#define USB1_IMAGES_DIR "/media/usb1/"
#define USB2_IMAGES_DIR "/media/usb2/"
#define USB3_IMAGES_DIR "/media/usb3/"

#define USB0_VIDEOS_DIR "/media/usb0/"
#define USB1_VIDEOS_DIR "/media/usb1/"
#define USB2_VIDEOS_DIR "/media/usb2/"
#define USB3_VIDEOS_DIR "/media/usb3/"

// TODO: Change this into a externally configurable list

/*

Considering that the pi has 4 USB ports, there is a possibility to connect 4 USB flash drives. The paths to them would be 
	/media/usb0
	/media/usb1
	/media/usb2
	/media/usb3
We need all of them and we search for mp4, jpg and png files there.

*/

namespace ofx {
namespace piMapper {

class MediaServer {
	public:
		MediaServer();
	
		void setup();
		void update();
		void draw();

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
		void addFboSource(FboSource * fboSource);
	
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
		DirectoryWatcher videoWatcher;
		DirectoryWatcher piVideoWatcher;
		DirectoryWatcher usb0VideoWatcher;
		DirectoryWatcher usb1VideoWatcher;
		DirectoryWatcher usb2VideoWatcher;
		DirectoryWatcher usb3VideoWatcher;
	
		DirectoryWatcher imageWatcher;
        DirectoryWatcher piImageWatcher;
		DirectoryWatcher usb0ImageWatcher;
		DirectoryWatcher usb1ImageWatcher;
		DirectoryWatcher usb2ImageWatcher;
		DirectoryWatcher usb3ImageWatcher;
	
        vector <string> _tempImagePaths;
        vector <string> _tempVideoPaths;
    
		map <string, BaseSource *> loadedSources;
	
		// FBO source storage before they go to loadedSources
		vector <FboSource *> fboSources; // FBO source storage
};

} // namespace piMapper
} // namespace ofx
