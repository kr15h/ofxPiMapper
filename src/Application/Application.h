#pragma once

#include <string>

// OpenFrameworks components
#include "ofEvents.h"
#include "ofLog.h"

// OfxPiMapper Components
#include "FboSource.h"
#include "Info.h"
#include "SurfaceStack.h"
#include "Gui.h"
#include "Vec2.h"

// Commands
#include "SetApplicationModeCmd.h"
#include "ClearSurfacesCmd.h"
#include "SetPresetCmd.h"
#include "AddSurfaceCmd.h"
#include "RmSurfaceCmd.h"
#include "MvLayerUpCmd.h"
#include "MvLayerDnCmd.h"
#include "DuplicateSurfaceCmd.h"
#include "FullscreenSurfaceCmd.h"
#include "TogglePerspectiveCmd.h"
#include "SetNextSourceCmd.h"
#include "ScaleSurfaceFromToCmd.h"
#include "AddGridRowCmd.h"
#include "RmGridRowCmd.h"
#include "AddGridColCmd.h"
#include "RmGridColCmd.h"
#include "SelNextSurfaceCmd.h"
#include "SelPrevSurfaceCmd.h"
#include "SelNextVertexCmd.h"
#include "SelPrevVertexCmd.h"
#include "SelVertexCmd.h"
#include "SelSurfaceCmd.h"
#include "MvSelectionCmd.h"
#include "ToggleAnimatedSourceCmd.h"
#include "SelNextTexCoordCmd.h"
#include "SelPrevTexCoordCmd.h"
#include "DeselectSurfaceCmd.h"
#include "SetVideoSourceCmd.h"

// Modes
#include "ApplicationBaseMode.h"
#include "PresentationMode.h"
#include "ProjectionMappingMode.h"
#include "TextureMappingMode.h"
#include "SourceSelectionMode.h"

// TODO: Move all command executors to here (Application class)
//       This would allow one not to repeat. Commands would be called in
//       one place and includes of commands would not be duplicated.

#define PIMAPPER_SETTINGS_FILE "ofxpimapper.xml"

namespace ofx {
namespace piMapper {

class ApplicationBaseMode;

class Application {

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
		void createSurface(SurfaceType type);
		void eraseSurface(int i);
		void setInfoText(std::string text);
		void toggleInfo();
		void togglePerspective();
		void saveProject();
		bool loadXmlSettings(std::string fileName);

		bool isShiftKeyDown();
		bool toggleShift();

		SurfaceManager * getSurfaceManager(){ return &_surfaceManager; }
		CmdManager * getCmdManager(){ return &_cmdManager; }
		MediaServer * getMediaServer(){ return &_mediaServer; }

		// Command executors
		void selectSurface(int i);
		void selectNextSurface();
		void selectPrevSurface();
		void selectNextVertex();
		void selectPrevVertex();
		void selectVertex(int surface, int vertex);
		void selectNextTexCoord();
		void selectPrevTexCoord();

		/*
		Context sensitive move.
		Moves vertex when in projection mapping mode.
		Moves texture coordinate when in texture mapping mode.
		*/
		void moveSelection(Vec3 by);

		void setPresentationMode();
		void setTextureMode();
		void setProjectionMode();
		void setSourceMode();
		void moveLayerUp();
		void moveLayerDown();
		void scaleUp();
		void scaleDown();
		void duplicateSurface();
        void setFullscreenSurface();
		void setNextSource();
		void setFboSource(std::string sourceId);
		void setVideoSource(std::string fileName, bool loop);
		void setImageSource(std::string fileName);
		void setDrawGui(bool drawGui);
		void addGridRow();
		void addGridColumn();
		void removeGridRow();
		void removeGridColumn();
		void togglePause();
		void moveTexCoord(int texCoordIndex, Vec2 by);
		// TODO: Add moveVertex.
		// Make it so that other parts of the application react to the change.
		void undo();
		void deselect();
		void toggleLayerPanel();

		void setPreset(unsigned int i);
		void setNextPreset();

		// System commands
		void reboot();
		void shutdown();

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
		bool _drawGui;

		float _lastSaveTime;
		float _autoSaveInterval;

		std::string _keySequence;

};

} // namespace piMapper
} // namespace ofx
