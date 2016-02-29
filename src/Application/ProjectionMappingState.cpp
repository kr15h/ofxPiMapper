#include "ProjectionMappingState.h"

namespace ofx {
namespace piMapper {

ProjectionMappingState * ProjectionMappingState::_instance = 0;

ProjectionMappingState * ProjectionMappingState::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::ProjectionMappingState();
	}
	return _instance;
}

void ProjectionMappingState::draw(Application * app){
	app->getGui()->draw();
}

void ProjectionMappingState::onKeyPressed(Application * app, ofKeyEventArgs & args){
	switch(args.key){
		 
	 case 't':
		 app->getCmdManager()->exec(
			 new AddSurfaceCmd(
				 app->getSurfaceManager(),
				 SurfaceType::TRIANGLE_SURFACE)
			 );
		 break;

	 case 'q':
		 app->getCmdManager()->exec(
			 new AddSurfaceCmd(
				 app->getSurfaceManager(),
				 SurfaceType::QUAD_SURFACE)
			 );
		 break;
		 
	 case 'g':
		 app->getCmdManager()->exec(
			 new AddSurfaceCmd(
				 app->getSurfaceManager(),
				 SurfaceType::GRID_WARP_SURFACE)
			 );
		break;

	 case OF_KEY_BACKSPACE:
		 if(app->getSurfaceManager()->getSelectedSurface() == 0){
			break;
		 }
		 app->getCmdManager()->exec(
			 new RmSurfaceCmd(app->getSurfaceManager()));
		 break;
	 
	 case 'p':
		 if(app->getSurfaceManager()->getSelectedSurface() == 0){
			break;
		 }
		 
		 if(app->getSurfaceManager()->getSelectedSurface()->getType() ==
			 SurfaceType::QUAD_SURFACE){
			 
			 app->getCmdManager()->exec(
				 new TogglePerspectiveCmd(
					 (QuadSurface *)app->getSurfaceManager()->getSelectedSurface() ) );
		 }
		 break;
	 
	 case '}':
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface()->getType() ==
				SurfaceType::GRID_WARP_SURFACE){
				
				// TODO: The command should not require projection editor pointer
				app->getCmdManager()->exec(
					new AddGridRowCmd(
						(GridWarpSurface *)app->getSurfaceManager()->getSelectedSurface() ));
			}
		 }
		 break;
	
	 case '{':
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface()->getType() ==
				SurfaceType::GRID_WARP_SURFACE){
				
				if(((GridWarpSurface *)app->getSurfaceManager()->getSelectedSurface())->getGridRows() > 1){
					// TODO: The command should not require projection editor pointer
					app->getCmdManager()->exec(
						new RmGridRowCmd(
							(GridWarpSurface *)app->getSurfaceManager()->getSelectedSurface() ));
				}
			}
		 }
		 break;
	 
	 case ']':
		if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface()->getType() ==
				SurfaceType::GRID_WARP_SURFACE){
				
				// TODO: The command should not require projection editor pointer
				app->getCmdManager()->exec(
					new AddGridColCmd(
						(GridWarpSurface *)app->getSurfaceManager()->getSelectedSurface() ));
			}
		 }
		 break;
		 
	 case '[':
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface()->getType() ==
				SurfaceType::GRID_WARP_SURFACE){
				
				if(((GridWarpSurface *)app->getSurfaceManager()->getSelectedSurface())->getGridCols() > 1){
					// TODO: The command should not require projection editor pointer
					app->getCmdManager()->exec(
						new RmGridColCmd(
							(GridWarpSurface *)app->getSurfaceManager()->getSelectedSurface() ));
				}
			}
		 }
		 break;
		 
	 case '.':
		 app->getCmdManager()->exec(new SelNextSurfaceCmd(app->getSurfaceManager()));
		 break;
		 
	 case ',':
		 app->getCmdManager()->exec(new SelPrevSurfaceCmd(app->getSurfaceManager()));
		 break;
		 
	 case '>':
		 app->getCmdManager()->exec(new SelNextVertexCmd(app->getSurfaceManager()));
		 break;
	 
	 case '<':
		 app->getCmdManager()->exec(new SelPrevVertexCmd(app->getSurfaceManager()));
		 break;
	 
	 case OF_KEY_UP:
		 if(app->isShiftKeyDown()){
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(0.0f, -10.0f)));
		 }else{
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(0.0f, -1.0f)));
		 }
		 break;
		 
	 case OF_KEY_DOWN:
		 if(app->isShiftKeyDown()){
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(0.0f, 10.0f)));
		 }else{
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(0.0f, 1.0f)));
		 }
		 break;
		 
	 case OF_KEY_LEFT:
		 if(app->isShiftKeyDown()){
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(-10.0f, 0.0f)));
		 }else{
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(-1.0f, 0.0f)));
		 }
		 break;
	 
	 case OF_KEY_RIGHT:
		 if(app->isShiftKeyDown()){
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(10.0f, 0.0f)));
		 }else{
			app->getCmdManager()->exec(new MvSelectionCmd(app->getSurfaceManager(), ofVec2f(1.0f, 0.0f)));
		 }
		 break;
		 
	 case ' ':
		 app->getCmdManager()->exec(new DeselectSurfaceCmd(app->getSurfaceManager()));
		 break;
		 
	 case OF_KEY_TAB:
		 app->getCmdManager()->exec(
			new SetNextSourceCmd(
				app->getSurfaceManager()->getSelectedSurface(),
				app->getGui()->getSourcesEditor()));
		 break;
		 
	 default:
		 break;
	}
}

void ProjectionMappingState::onJointPressed(Application * app, GuiJointEvent & e){
	app->getCmdManager()->exec(new SelVertexCmd(app->getSurfaceManager(), e.jointIndex));
	app->getCmdManager()->exec(new MvSurfaceVertCmd(
		e.jointIndex,
		app->getSurfaceManager()->getSelectedSurface()));
}

void ProjectionMappingState::onSurfacePressed(Application * app, GuiSurfaceEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != e.surface){
		app->getCmdManager()->exec(new SelSurfaceCmd(app->getSurfaceManager(), e.surface ));
	}
	
	app->getCmdManager()->exec(new StartDragSurfaceCmd(e.surface));
}

void ProjectionMappingState::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	app->getCmdManager()->exec(new DeselectSurfaceCmd(app->getSurfaceManager()));
}

} // namespace piMapper
} // namespace ofx