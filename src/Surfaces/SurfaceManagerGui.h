// TODO: Move this to the Application State system.

#pragma once

#include "ofEvents.h"
#include "ofGraphics.h"

#include "SurfaceManager.h"
#include "TextureEditor.h"
#include "ProjectionEditor.h"
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

		void mousePressed(ofMouseEventArgs & args);
		void mouseDragged(ofMouseEventArgs & args);

		void setSurfaceManager(SurfaceManager * newSurfaceManager);
		void setMediaServer(MediaServer * newMediaServer);
		void setCmdManager(CmdManager * cmdManager);

		void setMode(int newGuiMode);
		int getMode();
		void startDrag();
		void stopDrag();
	
		ProjectionEditor * getProjectionEditor();
		TextureEditor * getTextureEditor();
		SourcesEditor * getSourcesEditor();
	
		void onVertexChanged(int & i);
		void onVerticesChanged(vector<ofVec3f> & vertices);
		void onSurfaceSelected(int & surfaceIndex);
		void onVertexSelected(int & vertexIndex);
		void onVertexUnselected(int & vertexIndex);
	
		ofVec2f clickPosition;
		bool bDrag;

	private:
		SurfaceManager * surfaceManager;
		MediaServer * mediaServer;
		TextureEditor textureEditor;
		ProjectionEditor projectionEditor;
		SourcesEditor sourcesEditor;
	
		int guiMode;
	
		CmdManager * _cmdManager;

};

} // namespace piMapper
} // namespace ofx