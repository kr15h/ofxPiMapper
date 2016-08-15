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
	
	/*
		Draw layer panel / indicator consisting of layer icons.
		If none of the surfaces is selected, use outlines to represent all surfaces.
		If one of the surfaces is selected, use a filled rectangle to visualise its location
		in the layer stack.
	*/
	int numSurfaces = app->getSurfaceManager()->size();
	
	for(int i = 0; i < numSurfaces; ++i){
		BaseSurface * surface = app->getSurfaceManager()->getSurface(i);
		BaseSurface * surfaceSelected = app->getSurfaceManager()->getSelectedSurface();
		
		ofPushStyle();
		
		if(surface == surfaceSelected){
			ofFill();
		}else{
			ofNoFill();
		}
		
		int layerIconWidth = 20;
		int layerIconHeight = 20;
		int offsetRight = 20;
		int offsetTop = 20;
		int verticalSpacing = 10;
		int layerIconX = ofGetWidth() - offsetRight - layerIconWidth;
		int layerIconY = offsetTop + ((layerIconHeight + verticalSpacing) * (numSurfaces - i));
		
		ofRectangle layerIcon = ofRectangle(
			layerIconX,
			layerIconY,
			layerIconWidth,
			layerIconHeight);
		
		ofDrawRectangle(layerIcon);
		
		ofPopStyle();
	}
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
	
	 case 'd':
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			app->getCmdManager()->exec(
				new DuplicateSurfaceCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					app->getSurfaceManager()));
		 }
		 break;
		 
	 case '0': // Move selected surface up the layer stack
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface() ==
				SurfaceStack::instance()->at(SurfaceStack::instance()->size() - 1)){
				return;
			}
			
			app->getCmdManager()->exec(
				new MvLayerUpCmd(
					app->getSurfaceManager()->getSelectedSurface())
			);
		 }
		 break;
		
	 case '9': // Move selected surface down the layer stack
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface() ==
				SurfaceStack::instance()->at(0)){
				return;
			}
			
			app->getCmdManager()->exec(
				new MvLayerDnCmd(
					app->getSurfaceManager()->getSelectedSurface())
			);
		 }
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