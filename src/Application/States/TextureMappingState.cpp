#include "TextureMappingState.h"

namespace ofx {
namespace piMapper {

TextureMappingState * TextureMappingState::_instance = 0;

TextureMappingState * TextureMappingState::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::TextureMappingState();
	}
	return _instance;
}

TextureMappingState::TextureMappingState(){
	_bTranslateCanvas = false;
	_canvasTranslate = ofPoint(0, 0);
	_clickCanvasTranslate = ofPoint(0, 0);
	_drawMode = 0;
}

void TextureMappingState::draw(Application * app){
	if(_drawMode == 0){
		// Texture on the back
		ofPushMatrix();
		ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
		app->getGui()->draw();
	
		// Semi-transparent surfaces on the front
		ofPushStyle();
		ofSetColor(255, 255, 255, 150);
		app->getSurfaceManager()->draw();
		ofPopStyle();
		ofPopMatrix();
	}else if(_drawMode == 1){
		// Testure on the background
		ofPushMatrix();
		ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
		app->getGui()->draw();
	
		// Opaque surfaces on the front
		ofPushStyle();
		ofSetColor(255, 255, 255, 255);
		app->getSurfaceManager()->draw();
		ofPopStyle();
		ofPopMatrix();
	}else if(_drawMode == 2){
		// Texture only
		ofPushMatrix();
		ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
		app->getGui()->draw();
		ofPopMatrix();
	}else{
		_drawMode = 0;
	}
	
	ofPushMatrix();
	ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
	
	if(_drawMode != 2){
		Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
		Gui::instance()->getSurfaceHighlightWidget().draw();
	}
	
	Gui::instance()->getTextureHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getTextureHighlightWidget().draw();
	
	ofPopMatrix();
}

void TextureMappingState::onKeyPressed(Application * app, ofKeyEventArgs & args){
	switch(args.key){
		 
	 case '>':
		 app->getCmdManager()->exec(
			 new SelNextTexCoordCmd(app->getGui()->getTextureEditor()));
		 break;
		 
	 case '<':
		 app->getCmdManager()->exec(
			 new SelPrevTexCoordCmd(app->getGui()->getTextureEditor()));
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
					app->getGui()->getSourcesEditor()));
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

void TextureMappingState::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	// Exec the command only if a joint is selected.
	bool selected = false;
	for(unsigned int i = 0; i < app->getGui()->getTextureEditor()->getJoints().size(); ++i){
		if(app->getGui()->getTextureEditor()->getJoints()[i]->selected){
			selected = true;
			break;
		}
	}
	
	if(selected){
		app->getCmdManager()->exec(
			new DeselectTexCoordCmd(app->getGui()->getTextureEditor()));
	}
	
	_bTranslateCanvas = true;
}

void TextureMappingState::onMousePressed(Application * app, ofMouseEventArgs & args){
	_clickPosition = ofPoint(args.x, args.y);
	_prevCanvasTranslate = _canvasTranslate;

	// Alter mouse event args to match canvas translation
	args.x -= _canvasTranslate.x;
	args.y -= _canvasTranslate.y;
	app->getGui()->mousePressed(args);
}

void TextureMappingState::onMouseReleased(Application * app, ofMouseEventArgs & args){
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
	
	// Alter mouse event args to match canvas translation
	args.x -= _canvasTranslate.x;
	args.y -= _canvasTranslate.y;
	app->getGui()->mouseReleased(args);
}

void TextureMappingState::onMouseDragged(Application * app, ofMouseEventArgs & args){
	if(!_bTranslateCanvas){
		// Alter mouse event args to match canvas translation
		args.x -= _canvasTranslate.x;
		args.y -= _canvasTranslate.y;
		app->getGui()->mouseDragged(args);
	}else{
		ofPoint mousePosition = ofPoint(args.x, args.y);
		ofPoint distance =  mousePosition - _clickPosition;
		_canvasTranslate = _clickCanvasTranslate + distance;
	}
}

ofPoint TextureMappingState::getTranslation(){
	return _canvasTranslate;
}

void TextureMappingState::setTranslation(ofPoint p){
	_canvasTranslate = p;
	_clickCanvasTranslate = p;
}

void TextureMappingState::setDrawMode(int m){
	_drawMode = m;
}

int TextureMappingState::getDrawMode(){
	return _drawMode;
}

int TextureMappingState::getNextDrawMode(){
	int nextDrawMode = _drawMode + 1;
	
	if(nextDrawMode > 2){
		nextDrawMode = 0;
	}
	
	return nextDrawMode;
}

int TextureMappingState::getPrevDrawMode(){
	int prevDrawMode = _drawMode - 1;
	
	if(prevDrawMode < 0){
		prevDrawMode = 2;
	}
	
	return prevDrawMode;
}

} // namespace piMapper
} // namespace ofx