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

void SurfaceManagerGui::mousePressed(ofMouseEventArgs & args){
	if(guiMode == GuiMode::NONE){
		return;
	}else if(guiMode == GuiMode::TEXTURE_MAPPING){
		
		if(surfaceManager->getSelectedSurface() == 0){
			return;
		}
		
		CircleJoint * hitJoint = textureEditor.hitTestJoints(ofVec2f(args.x, args.y));
		
		if(hitJoint != 0){
		
			hitJoint->mousePressed(args);
			
			textureEditor.unselectAllJoints();
			hitJoint->select();
			hitJoint->startDrag();
			int jointIndex;
			
			for(int i = 0; i < textureEditor.getJoints().size(); i++){
				if(textureEditor.getJoints()[i] == hitJoint){
					jointIndex = i;
					break;
				}
			}

			_cmdManager->exec(new MvTexCoordCmd(jointIndex, &textureEditor));
			
		}else if(surfaceManager->getSelectedSurface()->getTextureHitArea().inside(args.x, args.y)){
			
			clickPosition = ofVec2f(args.x, args.y);
			startDrag();

			// TODO: emit event through the gui singleton
			_cmdManager->exec(new MvAllTexCoordsCmd(
				surfaceManager->getSelectedSurface(),
				&textureEditor));

		}else{
            Gui::instance()->notifyBackgroundPressed(args);
		}
	}
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
	
	projectionEditor.setSurfaceManager(surfaceManager);
	sourcesEditor.setSurfaceManager(surfaceManager);
}

// Set external media server so we can access it from wherever we need
void SurfaceManagerGui::setMediaServer(MediaServer * newMediaServer){
	mediaServer = newMediaServer;
	// Set the media server of the sources editor here
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
		//string sourceName = surfaceManager->getSelectedSurfaceSourceName();
		//sourcesEditor.selectImageSourceRadioButton(sourceName);
	}else{
		sourcesEditor.disable();
	}

	if(guiMode == GuiMode::TEXTURE_MAPPING){
		textureEditor.enable();
		// refresh texture editor surface reference
		textureEditor.setSurface(surfaceManager->getSelectedSurface());
	}else{
		textureEditor.disable();
	}

	if(guiMode == GuiMode::PROJECTION_MAPPING){
		projectionEditor.enable();
	}else{
		projectionEditor.disable();
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

ProjectionEditor * SurfaceManagerGui::getProjectionEditor(){
	return &projectionEditor;
}

TextureEditor * SurfaceManagerGui::getTextureEditor(){
	return &textureEditor;
}

SourcesEditor * SurfaceManagerGui::getSourcesEditor(){
	return &sourcesEditor;
}

void SurfaceManagerGui::onVertexChanged(int & i){
	bool isDragged = projectionEditor.getJoints()->at(i)->isDragged();
	projectionEditor.createJoints();
	projectionEditor.getJoints()->at(i)->select();
	if(isDragged){
		projectionEditor.getJoints()->at(i)->startDrag();
	}else{
		projectionEditor.getJoints()->at(i)->stopDrag();
	}
}

void SurfaceManagerGui::onVerticesChanged(vector<ofVec3f> & vertices){
	projectionEditor.createJoints();
}

void SurfaceManagerGui::onSurfaceSelected(int & surfaceIndex){
	projectionEditor.createJoints();
}

void SurfaceManagerGui::onVertexSelected(int & vertexIndex){
	if(projectionEditor.getJoints()->size() == 0){
		return;
	}
	
	projectionEditor.unselectAllJoints();
	projectionEditor.getJoints()->at(vertexIndex)->select();
}

void SurfaceManagerGui::onVertexUnselected(int & vertexIndex){
	if(projectionEditor.getJoints()->size() == 0){
		return;
	}
	
	projectionEditor.unselectAllJoints();
}

} // namespace piMapper
} // namespace ofx