#include "SurfaceManagerGui.h"

namespace ofx {
namespace piMapper {

SurfaceManagerGui::SurfaceManagerGui(){
	surfaceManager = 0;
	guiMode = GuiMode::NONE;
	bDrag = false;
	ofHideCursor();
	_cmdManager = 0;
}

void SurfaceManagerGui::setSurfaceManager(SurfaceManager * newSurfaceManager){
	if(surfaceManager == 0){
		ofRemoveListener(newSurfaceManager->vertexChangedEvent, this, &SurfaceManagerGui::onVertexChanged);
		ofRemoveListener(newSurfaceManager->verticesChangedEvent, this, &SurfaceManagerGui::onVerticesChanged);
		ofRemoveListener(newSurfaceManager->surfaceSelectedEvent, this, &SurfaceManagerGui::onSurfaceSelected);
		ofRemoveListener(newSurfaceManager->vertexSelectedEvent, this, &SurfaceManagerGui::onVertexSelected);
		ofRemoveListener(newSurfaceManager->vertexUnselectedEvent, this, &SurfaceManagerGui::onVertexUnselected);
	}
	
	surfaceManager = newSurfaceManager;
	
	ofAddListener(newSurfaceManager->vertexChangedEvent, this, &SurfaceManagerGui::onVertexChanged);
	ofAddListener(newSurfaceManager->verticesChangedEvent, this, &SurfaceManagerGui::onVerticesChanged);
	ofAddListener(newSurfaceManager->surfaceSelectedEvent, this, &SurfaceManagerGui::onSurfaceSelected);
	ofAddListener(newSurfaceManager->vertexSelectedEvent, this, &SurfaceManagerGui::onVertexSelected);
	ofAddListener(newSurfaceManager->vertexUnselectedEvent, this, &SurfaceManagerGui::onVertexUnselected);
	
	projectionEditorWidget.setSurfaceManager(surfaceManager);
	sourcesEditor.setSurfaceManager(surfaceManager);
}

void SurfaceManagerGui::setMediaServer(MediaServer * newMediaServer){
	mediaServer = newMediaServer;
	sourcesEditor.setMediaServer(mediaServer);
}

void SurfaceManagerGui::setCmdManager(CmdManager * cmdManager){
	_cmdManager = cmdManager;
	sourcesEditor.setCmdManager(_cmdManager);
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

	if(guiMode == GuiMode::SOURCE_SELECTION){
		sourcesEditor.enable();
	}else{
		sourcesEditor.disable();
	}

	if(guiMode == GuiMode::PROJECTION_MAPPING){
		projectionEditorWidget.enable();
	}else{
		projectionEditorWidget.disable();
	}
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

ProjectionEditorWidget * SurfaceManagerGui::getProjectionEditorWidget(){
	return &projectionEditorWidget;
}

SourcesEditor * SurfaceManagerGui::getSourcesEditor(){
	return &sourcesEditor;
}

void SurfaceManagerGui::onVertexChanged(int & i){
	bool isDragged = projectionEditorWidget.getJoints()->at(i)->isDragged();
	projectionEditorWidget.createJoints();
	projectionEditorWidget.getJoints()->at(i)->select();
	if(isDragged){
		projectionEditorWidget.getJoints()->at(i)->startDrag();
	}else{
		projectionEditorWidget.getJoints()->at(i)->stopDrag();
	}
}

void SurfaceManagerGui::onVerticesChanged(vector<ofVec3f> & vertices){
	projectionEditorWidget.createJoints();
}

void SurfaceManagerGui::onSurfaceSelected(int & surfaceIndex){
	projectionEditorWidget.createJoints();
}

void SurfaceManagerGui::onVertexSelected(int & vertexIndex){
	if(projectionEditorWidget.getJoints()->size() == 0){
		return;
	}
	
	projectionEditorWidget.unselectAllJoints();
	projectionEditorWidget.getJoints()->at(vertexIndex)->select();
}

void SurfaceManagerGui::onVertexUnselected(int & vertexIndex){
	if(projectionEditorWidget.getJoints()->size() == 0){
		return;
	}
	
	projectionEditorWidget.unselectAllJoints();
}

} // namespace piMapper
} // namespace ofx