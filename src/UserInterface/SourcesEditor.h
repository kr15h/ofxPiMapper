#pragma once

#include "ofGraphics.h"
#include "ofEvents.h"
#include "SurfaceManager.h"
#include "RadioList.h"
#include "MediaServer.h"
#include "CmdManager.h"
#include "SetSourceCmd.h"

namespace ofx {
namespace piMapper {

class SourcesEditor {
	public:
		// Default contructor that initializes media server locally,
		// thus requiring to delete the media server from memory on deconstr
		SourcesEditor();

		// Alternative constructor that allows to assign external media server
		SourcesEditor(MediaServer * externalMediaServer);
		~SourcesEditor();

		void registerAppEvents();
		void unregisterAppEvents();

		void setup(ofEventArgs & args);
		void draw();
		void loadImage(string name, string path);
		void disable();
		void enable();
		void setSurfaceManager(SurfaceManager * newSurfaceManager);
		void setCmdManager(CmdManager * cmdManager);

		// Sets external MediaServer
		void setMediaServer(MediaServer * newMediaServer);
		//void selectImageSourceRadioButton(string name);
		void selectSourceRadioButton(string & sourcePath);

		int getLoadedTexCount();
		ofTexture * getTexture(int index);

		void setImageSource(string & imagePath);
		void setVideoSource(string & videoPath);
		void setFboSource(string & fboName);
		void clearSource();

	private:
		MediaServer * mediaServer;
		SurfaceManager * surfaceManager;
		RadioList * imageSelector;
		RadioList * videoSelector;
		RadioList * fboSelector;
		CmdManager * _cmdManager;

		// Is the media server pointer local or from somewhere else?
		// We use this to determine if we are allowed to clear media server locally.
		bool isMediaServerExternal;

		// Init handles variable initialization in all constructors
		void init();

		// Methods for adding and removing listeners to the media server
		void addMediaServerListeners();
		void removeMediaServerListeners();

		// Handles GUI event, whenever someone has clicked on a radio button
		void handleImageSelected(string & imagePath);
		void handleVideoSelected(string & videoPath);
		void handleFboSelected(string & fboName);

		// Careful clearing of the media server,
		// clears only if the media server has been initialized locally
		void clearMediaServer();

		// MediaServer event handlers
		void handleImageAdded(string & path);
		void handleImageRemoved(string & path);
		void handleVideoAdded(string & path);
		void handleVideoRemoved(string & path);
		void handleImageLoaded(string & path);
		void handleImageUnloaded(string & path);
		void handleFboSourceAdded(string & name);
		void handleFboSourceRemoved(string & name);
		void handleFboSourceLoaded(string & name);
		void handleFboSourceUnloaded(string & name);

};

} // namespace piMapper
} // namespace ofx