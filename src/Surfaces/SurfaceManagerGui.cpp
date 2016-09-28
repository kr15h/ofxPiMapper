#include "SurfaceManagerGui.h"

namespace ofx {
namespace piMapper {

SurfaceManagerGui::SurfaceManagerGui(){
	guiMode = GuiMode::NONE;
	bDrag = false;
	ofHideCursor();
	_cmdManager = 0;
}

void SurfaceManagerGui::setMediaServer(MediaServer * newMediaServer){
	mediaServer = newMediaServer;
}

void SurfaceManagerGui::setCmdManager(CmdManager * cmdManager){
	_cmdManager = cmdManager;
}

void SurfaceManagerGui::setMode(int newGuiMode){
	if(newGuiMode != GuiMode::NONE && newGuiMode != GuiMode::TEXTURE_MAPPING &&
	   newGuiMode != GuiMode::PROJECTION_MAPPING &&
	   newGuiMode != GuiMode::SOURCE_SELECTION){
		throw runtime_error("Trying to set invalid mode.");
	}

	if(newGuiMode == GuiMode::NONE){
		ofHideCursor();
	}else{
		ofShowCursor();
	}

	guiMode = newGuiMode;
}

int SurfaceManagerGui::getMode(){
	return guiMode;
}

void SurfaceManagerGui::startDrag(){
	bDrag = true;
}

void SurfaceManagerGui::stopDrag(){
	bDrag = false;
}

} // namespace piMapper
} // namespace ofx