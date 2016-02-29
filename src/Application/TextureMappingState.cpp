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

void TextureMappingState::draw(Application * app){
	app->getGui()->draw();
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
		 app->getCmdManager()->exec(
			new DeselectTexCoordCmd(app->getGui()->getTextureEditor()));
		 break;
		 
	 case OF_KEY_TAB:
		 app->getCmdManager()->exec(
			new SetNextSourceCmd(
				app->getSurfaceManager()->getSelectedSurface(),
				app->getGui()->getSourcesEditor()));
		 break;
	}
	
}

} // namespace piMapper
} // namespace ofx