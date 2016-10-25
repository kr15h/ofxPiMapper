#pragma once

#include "ofEvents.h"
#include "ofLog.h"

#include "SetApplicationModeCmd.h"
#include "ClearSurfacesCmd.h"
#include "SetPresetCmd.h"

#include "ApplicationBaseMode.h"
#include "PresentationMode.h"
#include "ProjectionMappingMode.h"
#include "TextureMappingMode.h"
#include "SourceSelectionMode.h"
#include "FboSource.h"
#include "Info.h"

#include "SurfaceStack.h"

// TODO: To be removed.
#include "GuiMode.h"

#include "Gui.h"
#include "TerminalListener.h"

#define PIMAPPER_SETTINGS_FILE "ofxpimapper.xml"

namespace ofx {
namespace piMapper {

class ApplicationBaseMode;

class Application : public KeyListener {

	public:
		Application();

		ApplicationBaseMode * getState();

		void setup();
		void update();
		void draw();
	
		void onKeyPressed(ofKeyEventArgs & args);
		void onKeyReleased(ofKeyEventArgs & args);
	
		// We use this to pass mouse events into the GUI layer
		void onMousePressed(ofMouseEventArgs & args);
		void onMouseReleased(ofMouseEventArgs & args);
		void onMouseDragged(ofMouseEventArgs & args);
	
		// Then we catch GUI events with this one and create commands
		void onJointPressed(GuiJointEvent & e);
		void onSurfacePressed(GuiSurfaceEvent & e);
		void onBackgroundPressed(GuiBackgroundEvent & e);
	
		void onGuiEvent(GuiEvent & e);
	
		void addFboSource(FboSource & fboSource);
		void addFboSource(FboSource * fboSource);
		void saveProject();
	
		bool loadXmlSettings(string fileName);
		bool isShiftKeyDown();
	
		SurfaceManager * getSurfaceManager(){ return &_surfaceManager; }
		CmdManager * getCmdManager(){ return &_cmdManager; }
		MediaServer * getMediaServer(){ return &_mediaServer; }
	
		void onCharacterReceived(KeyListenerEventData & e);
		TerminalListener consoleListener;
	
		// Command executors
		void setPresentationMode();
		void setTextureMode();
		void setProjectionMode();
		void setSourceMode();
	
		void setPreset(unsigned int i);
		void setNextPreset();
	
	protected:
		void setState(ApplicationBaseMode * st);
	
	private:
		friend class ApplicationBaseMode;
		friend class SetApplicationModeCmd;

		ApplicationBaseMode * _state;
	
		CmdManager _cmdManager;
		MediaServer _mediaServer;
		SurfaceManager _surfaceManager;
		Info _info;
	
		bool _shiftKeyDown;
        bool _isSSHConnection;
	
		float _lastSaveTime;
		float _autoSaveInterval;
	
		string _keySequence;

};

} // namespace piMapper
} // namespace ofx
