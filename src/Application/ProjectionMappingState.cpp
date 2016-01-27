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

	 default:
		 break;
	}
}

} // namespace piMapper
} // namespace ofx