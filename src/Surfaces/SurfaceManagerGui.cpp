#include "SurfaceManagerGui.h"

namespace ofx {
namespace piMapper {

SurfaceManagerGui::SurfaceManagerGui(){
	surfaceManager = 0;
	guiMode = GuiMode::NONE;
	bDrag = false;
	registerMouseEvents();
	ofHideCursor();
	_cmdManager = 0;
}

SurfaceManagerGui::~SurfaceManagerGui(){
	unregisterMouseEvents();
	surfaceManager = 0;
	_cmdManager = 0;
}

void SurfaceManagerGui::registerMouseEvents(){
	//ofAddListener(ofEvents().mousePressed, this,
	//			  &SurfaceManagerGui::mousePressed);
	//ofAddListener(ofEvents().mouseReleased, this,
	//			  &SurfaceManagerGui::mouseReleased);
	//ofAddListener(ofEvents().mouseDragged, this,
	//			  &SurfaceManagerGui::mouseDragged);
}

void SurfaceManagerGui::unregisterMouseEvents(){
	//ofRemoveListener(ofEvents().mousePressed, this,
	//				 &SurfaceManagerGui::mousePressed);
	//ofRemoveListener(ofEvents().mouseReleased, this,
	//				 &SurfaceManagerGui::mouseReleased);
	//ofRemoveListener(ofEvents().mouseDragged, this,
	//				 &SurfaceManagerGui::mouseDragged);
}

void SurfaceManagerGui::draw(){
	if(surfaceManager == 0){
		return;
	}

	if(guiMode == GuiMode::TEXTURE_MAPPING){
		// draw the texture of the selected surface
		if(surfaceManager->getSelectedSurface() != 0){
			bool normalizedTexCoords = ofGetUsingNormalizedTexCoords();
			ofEnableNormalizedTexCoords();
			
			// Reset default color to white first
			ofSetColor(255, 255, 255, 255);
			surfaceManager->getSelectedSurface()->drawTexture(ofVec2f(0, 0));
			
			if(!normalizedTexCoords){
				ofDisableNormalizedTexCoords();
			}
		}

		// draw texture editing GUI on top
		textureEditor.draw();
	}else if(guiMode == GuiMode::PROJECTION_MAPPING){
		projectionEditor.draw();
	}else if(guiMode == GuiMode::SOURCE_SELECTION){
		sourcesEditor.draw();
	}
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

	}else if(guiMode == GuiMode::PROJECTION_MAPPING){
		CircleJoint * hitJoint = 0;
		int hitJointIndex = -1;
		BaseSurface * hitSurface = 0;

		hitJoint = projectionEditor.hitTestJoints(ofVec2f(args.x, args.y));
		
		if(hitJoint){
			for(int i = projectionEditor.getJoints()->size() - 1; i >= 0 ; --i){
				if((*projectionEditor.getJoints())[i] == hitJoint){
					hitJointIndex = i;
					break;
				}
			}
		}else{
			for(int i = surfaceManager->size() - 1; i >= 0; --i){
				if(surfaceManager->getSurface(i)->hitTest(ofVec2f(args.x, args.y))){
					hitSurface = surfaceManager->getSurface(i);
					break;
				}
			}
		}
		
		if(Gui::instance()->getScaleWidget().inside(args.x, args.y)){
			//
		}else if(hitJoint){
			hitJoint->select();
			hitJoint->startDrag();
			Gui::instance()->notifyJointPressed(args, hitJointIndex);
		}else if(hitSurface){
			clickPosition = ofVec2f(args.x, args.y);
			startDrag(); // TODO: Should be something like `hitSurface->startDrag()`
			Gui::instance()->notifySurfacePressed(args, hitSurface);
		}else{
			Gui::instance()->notifyBackgroundPressed(args);
		}
	}else if(guiMode == GuiMode::SOURCE_SELECTION){}
}

void SurfaceManagerGui::mouseReleased(ofMouseEventArgs & args){
	stopDrag();
	projectionEditor.stopDragJoints();
	textureEditor.stopDragJoints();

	// Check if surface has moved
	if(surfaceManager->getSelectedSurface()){
		if(!surfaceManager->getSelectedSurface()->getMoved()){
			
			// TODO: emit event through the gui singleton
			//_cmdManager->undo();
		}
	}
}

void SurfaceManagerGui::mouseDragged(ofMouseEventArgs & args){
	if(guiMode == GuiMode::TEXTURE_MAPPING){
		textureEditor.mouseDragged(args);
	}else if(guiMode == GuiMode::PROJECTION_MAPPING){
		projectionEditor.mouseDragged(args);
	}
	
	if(bDrag){
		ofVec2f mousePosition = ofVec2f(args.x, args.y);
		ofVec2f distance = mousePosition - clickPosition;

		if(guiMode == GuiMode::PROJECTION_MAPPING){
			
			// Moves the selected surface on drag
			projectionEditor.moveSelectedSurface(distance);
		}else if(guiMode == GuiMode::TEXTURE_MAPPING){
		
			// Moves the crop area of the texture
			textureEditor.moveTexCoords(distance);
		}
		clickPosition = mousePosition;
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
	//cout << "VERTEX CHANGED: " << vertex.x << ", " << vertex.y << endl;
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
	//cout << "VERTICES CHANGED: " << vertices.size() << endl;
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