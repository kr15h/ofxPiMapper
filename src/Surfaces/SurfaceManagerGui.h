// TODO: Move this to the Application State system.

#pragma once

#include "ofEvents.h"
#include "ofGraphics.h"

#include "SurfaceManager.h"
#include "SourcesEditor.h"
#include "GuiMode.h"
#include "CmdManager.h"
#include "SelSurfaceCmd.h"
#include "MvSurfaceVertCmd.h"
#include "MvAllTexCoordsCmd.h"
#include "MvTexCoordCmd.h"
#include "SelVertexCmd.h"
#include "DeselectSurfaceCmd.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class SurfaceManagerGui {
	
    public:
		SurfaceManagerGui();
	
		void setMediaServer(MediaServer * newMediaServer);
		void setCmdManager(CmdManager * cmdManager);

		void setMode(int newGuiMode);
		int getMode();
		void startDrag();
		void stopDrag();
	
		SourcesEditor * getSourcesEditor();
	
		ofVec2f clickPosition;
		bool bDrag;

	private:
		SurfaceManager * surfaceManager;
		MediaServer * mediaServer;
		SourcesEditor sourcesEditor;
	
		int guiMode;
	
		CmdManager * _cmdManager;

};

} // namespace piMapper
} // namespace ofx