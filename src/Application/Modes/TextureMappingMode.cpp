#include "TextureMappingMode.h"

namespace ofx {
namespace piMapper {

TextureMappingMode * TextureMappingMode::_instance = 0;

TextureMappingMode * TextureMappingMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::TextureMappingMode();
	}
	return _instance;
}

TextureMappingMode::TextureMappingMode(){
	_bTranslateCanvas = false;
	_canvasTranslate = ofPoint(0, 0);
	_clickCanvasTranslate = ofPoint(0, 0);
	_drawMode = 0;
}

void TextureMappingMode::setup(Application * app){
	Gui::instance()->getTextureHighlightWidget().setSurfaceManager(app->getSurfaceManager());
}

void TextureMappingMode::update(Application * app){
	Gui::instance()->getTextureEditorWidget().update();
}

void TextureMappingMode::draw(Application * app){
	
	// TODO: Make state classes out of the following anti-code.
	
	if(_drawMode == 0){ // Semi-transparent surfaces on front
		ofPushMatrix();
		ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
		drawTexture(app);
		ofPopMatrix();
		
		ofPushStyle();
		ofSetColor(255, 255, 255, 150);
		app->getSurfaceManager()->draw();
		ofPopStyle();
	}else if(_drawMode == 1){ // Opaque surfaces on front
		ofPushMatrix();
		ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
		drawTexture(app);
		ofPopMatrix();
		
		ofPushStyle();
		ofSetColor(255, 255, 255, 255);
		app->getSurfaceManager()->draw();
		ofPopStyle();
	}else if(_drawMode == 2){ // Draw texture only
		ofPushMatrix();
		ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
		drawTexture(app);
		ofPopMatrix();
	}else{
		_drawMode = 0;
	}
	
	if(_drawMode != 2){
		Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
		Gui::instance()->getSurfaceHighlightWidget().draw();
	}
	
	ofPushMatrix();
	ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
	Gui::instance()->getTextureHighlightWidget().draw();
	Gui::instance()->getTextureEditorWidget().draw();
	ofPopMatrix();
}

void TextureMappingMode::onKeyPressed(Application * app, ofKeyEventArgs & args){
	int key = args.key;
	float moveStep;

	if(app->isShiftKeyDown()){
		moveStep = 10.0f;
	}else{
		moveStep = 1.0f;
	}
	
	switch(args.key){

	 case OF_KEY_LEFT:
		 moveSelection(app, ofVec2f(-moveStep, 0.0f));
		 break;

	 case OF_KEY_RIGHT:
		 moveSelection(app, ofVec2f(moveStep, 0.0f));
		 break;

	 case OF_KEY_UP:
		 moveSelection(app, ofVec2f(0.0f, -moveStep));
		 break;

	 case OF_KEY_DOWN:
		 moveSelection(app, ofVec2f(0.0f, moveStep));
		 break;

	 case '>':
		 app->getCmdManager()->exec(
			 new SelNextTexCoordCmd(&Gui::instance()->getTextureEditorWidget()));
		 break;
		 
	 case '<':
		 app->getCmdManager()->exec(
			 new SelPrevTexCoordCmd(&Gui::instance()->getTextureEditorWidget()));
		 break;
	 
	 case ' ':
		 if(app->getSurfaceManager()->getSelectedSurface() == 0){
			return;
		 }
		 
         if(app->getSurfaceManager()->getSelectedSurface()->getSource()->getType() ==
            SourceType::SOURCE_TYPE_VIDEO){
            app->getCmdManager()->exec(
                new ToggleAnimatedSourceCmd(
                    app->getSurfaceManager()->getSelectedSurface()));
         }
		 break;
		 
	 case OF_KEY_TAB:
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			app->getCmdManager()->exec(
				new SetNextSourceCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					&Gui::instance()->getSourcesEditorWidget()));
		 }else{
			app->getCmdManager()->exec(new SelNextSurfaceCmd(app->getSurfaceManager()));
		 }
		 break;
	
	 case '0': // Next draw mode
		 app->getCmdManager()->exec(new SetTexMapDrawModeCmd( this, getNextDrawMode() ));
		 break;
	 
	 case '9': // Prew draw mode
		 app->getCmdManager()->exec(new SetTexMapDrawModeCmd( this, getPrevDrawMode() ));
		 break;
		 
	}
}

void TextureMappingMode::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	// Exec the command only if a joint is selected.
	bool selected = false;
	for(unsigned int i = 0; i < Gui::instance()->getTextureEditorWidget().getJoints().size(); ++i){
		if(Gui::instance()->getTextureEditorWidget().getJoints()[i]->selected){
			selected = true;
			break;
		}
	}
	
	if(selected){
		app->getCmdManager()->exec(
			new DeselectTexCoordCmd(&Gui::instance()->getTextureEditorWidget()));
	}
	
	_bTranslateCanvas = true;
}

void TextureMappingMode::onMousePressed(Application * app, ofMouseEventArgs & args){
	_clickPosition = ofPoint(args.x, args.y);
	_prevCanvasTranslate = _canvasTranslate;

	// Alter mouse event args to match canvas translation
	args.x -= _canvasTranslate.x;
	args.y -= _canvasTranslate.y;
	
	if(app->getSurfaceManager()->getSelectedSurface() == 0){
		return;
	}
	
	CircleJoint * hitJoint =
		Gui::instance()->getTextureEditorWidget().hitTestJoints(ofVec2f(args.x, args.y));
	
	if(hitJoint != 0){
	
		hitJoint->mousePressed(args);
		
		Gui::instance()->getTextureEditorWidget().unselectAllJoints();
		hitJoint->select();
		hitJoint->startDrag();
		int jointIndex;
		
		for(int i = 0; i < Gui::instance()->getTextureEditorWidget().getJoints().size(); i++){
			if(Gui::instance()->getTextureEditorWidget().getJoints()[i] == hitJoint){
				jointIndex = i;
				break;
			}
		}

		app->getCmdManager()->exec(
			new MvTexCoordCmd(jointIndex, &Gui::instance()->getTextureEditorWidget()));
		
	}else if(app->getSurfaceManager()->getSelectedSurface()->getTextureHitArea().inside(args.x, args.y)){
		
		_clickPosition = ofPoint(args.x, args.y);
		_bCropAreaDrag = true;

		// TODO: emit event through the gui singleton
		app->getCmdManager()->exec(new MvAllTexCoordsCmd(
			app->getSurfaceManager()->getSelectedSurface(),
			&Gui::instance()->getTextureEditorWidget()));

	}else{
           Gui::instance()->notifyBackgroundPressed(args);
	}
}

void TextureMappingMode::onMouseReleased(Application * app, ofMouseEventArgs & args){
	_bTranslateCanvas = false;
	
	// If translation has happened, create an undoable command
	if(_prevCanvasTranslate != _canvasTranslate){
		app->getCmdManager()->exec(
			new TranslateCanvasCmd(
				app,
				_prevCanvasTranslate,
				_canvasTranslate));
	}
	
	_clickCanvasTranslate = _canvasTranslate;
	
	args.x -= _canvasTranslate.x;
	args.y -= _canvasTranslate.y;

	_bCropAreaDrag = false;
	Gui::instance()->getTextureEditorWidget().stopDragJoints();
}

// TODO: Handle app->getGui()->clickPosition and app->getGui()->bDrag locally.
void TextureMappingMode::onMouseDragged(Application * app, ofMouseEventArgs & args){
	if(!_bTranslateCanvas){
		args.x -= _canvasTranslate.x;
		args.y -= _canvasTranslate.y;
		Gui::instance()->getTextureEditorWidget().onMouseDragged(args);
		
		if(_bCropAreaDrag){
			ofPoint mousePosition = ofPoint(args.x, args.y);
			ofPoint distance = mousePosition - _clickPosition;
			Gui::instance()->getTextureEditorWidget().moveTexCoords(distance);
			_clickPosition = mousePosition;
		}
	}else{
		ofPoint mousePosition = ofPoint(args.x, args.y);
		ofPoint distance =  mousePosition - _clickPosition;
		_canvasTranslate = _clickCanvasTranslate + distance;
	}
}

void TextureMappingMode::drawTexture(Application * app){
	if(app->getSurfaceManager()->getSelectedSurface() != 0){
		bool normalizedTexCoords = ofGetUsingNormalizedTexCoords();
		ofEnableNormalizedTexCoords();

		ofSetColor(255, 255, 255, 255);
		app->getSurfaceManager()->getSelectedSurface()->drawTexture(ofVec2f(0, 0));

		if(!normalizedTexCoords){
			ofDisableNormalizedTexCoords();
		}
	}
}

void TextureMappingMode::moveSelection(Application * app, ofVec2f by){
	// TODO: Create an undoable command out of this
	Gui::instance()->getTextureEditorWidget().moveSelection(by);
}

ofPoint TextureMappingMode::getTranslation(){
	return _canvasTranslate;
}

void TextureMappingMode::setTranslation(ofPoint p){
	_canvasTranslate = p;
	_clickCanvasTranslate = p;
}

void TextureMappingMode::setDrawMode(int m){
	_drawMode = m;
}

int TextureMappingMode::getDrawMode(){
	return _drawMode;
}

int TextureMappingMode::getNextDrawMode(){
	int nextDrawMode = _drawMode + 1;
	
	if(nextDrawMode > 2){
		nextDrawMode = 0;
	}
	
	return nextDrawMode;
}

int TextureMappingMode::getPrevDrawMode(){
	int prevDrawMode = _drawMode - 1;
	
	if(prevDrawMode < 0){
		prevDrawMode = 2;
	}
	
	return prevDrawMode;
}

} // namespace piMapper
} // namespace ofx