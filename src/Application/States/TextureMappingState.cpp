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
	app->getSurfaceManager()->draw();
	
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSurfaceHighlightWidget().draw();
	
	Gui::instance()->getTextureHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getTextureHighlightWidget().draw();
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
	}
}

void TextureMappingState::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
    app->getCmdManager()->exec(
        new DeselectTexCoordCmd(app->getGui()->getTextureEditor()));
}

} // namespace piMapper
} // namespace ofx