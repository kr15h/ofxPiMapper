#include "ProjectionMappingMode.h"

namespace ofx {
namespace piMapper {

ProjectionMappingMode::ProjectionMappingMode(){
	_surfaceScaleBeforeTransform = 1.0f;
}

ProjectionMappingMode * ProjectionMappingMode::_instance = 0;

ProjectionMappingMode * ProjectionMappingMode::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::ProjectionMappingMode();
	}
	return _instance;
}

void ProjectionMappingMode::setup(Application *app){
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getLayerPanelWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getProjectionEditorWidget().setSurfaceManager(app->getSurfaceManager());
}

void ProjectionMappingMode::update(Application * app){
	Gui::instance()->getProjectionEditorWidget().update();
	Gui::instance()->getScaleWidget().update();
}

void ProjectionMappingMode::draw(Application * app){
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	app->getSurfaceManager()->draw();
	ofPopStyle();
	
	Gui::instance()->getProjectionEditorWidget().draw();
	
	// Draw scale widget. The size of the widget is being set on surface select.
	BaseSurface * selectedSurface = app->getSurfaceManager()->getSelectedSurface();
	if(selectedSurface != 0){
		Gui::instance()->getScaleWidget().draw();
	}
	
	Gui::instance()->getLayerPanelWidget().draw();
	Gui::instance()->getSurfaceHighlightWidget().draw();
}

void ProjectionMappingMode::onKeyPressed(Application * app, ofKeyEventArgs & args){
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
					&Gui::instance()->getSourcesEditorWidget()));
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
				app->getSurfaceManager()->getActivePreset()->at(
					app->getSurfaceManager()->getActivePreset()->size() - 1)){
				return;
			}
			
			app->getCmdManager()->exec(
				new MvLayerUpCmd(
					app->getSurfaceManager()->getActivePreset(),
					app->getSurfaceManager()->getSelectedSurface())
			);
		 }
		 break;
		
	 case '9': // Move selected surface down the layer stack
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface() ==
				app->getSurfaceManager()->getActivePreset()->at(0)){
				return;
			}
			
			app->getCmdManager()->exec(
				new MvLayerDnCmd(
					app->getSurfaceManager()->getActivePreset(),
					app->getSurfaceManager()->getSelectedSurface())
			);
		 }
		 break;
		 
	 case '+': // Scale surface up
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			app->getCmdManager()->exec(
				new ScaleSurfaceFromToCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					app->getSurfaceManager()->getSelectedSurface()->getScale(),
					app->getSurfaceManager()->getSelectedSurface()->getScale() + 0.2f));
		 }
		 break;

	 case '-': // Scale surface down
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			if(app->getSurfaceManager()->getSelectedSurface()->getScale() <= 0.21f){
				break;
			}
			app->getCmdManager()->exec(
				new ScaleSurfaceFromToCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					app->getSurfaceManager()->getSelectedSurface()->getScale(),
					app->getSurfaceManager()->getSelectedSurface()->getScale() - 0.2f));
		 }
		 break;
		 
	 case 'n': // Set next preset
		 app->getSurfaceManager()->setNextPreset();
		 break;
		 
	 default:
		 break;
	}
}

void ProjectionMappingMode::onMousePressed(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMousePressed(args);
	
	CircleJoint * hitJoint = 0;
	int hitJointIndex = -1;
	BaseSurface * hitSurface = 0;

	hitJoint = Gui::instance()->getProjectionEditorWidget().hitTestJoints(ofVec2f(args.x, args.y));
		
	if(hitJoint){
		for(int i = Gui::instance()->getProjectionEditorWidget().getJoints()->size() - 1; i >= 0 ; --i){
			if((*Gui::instance()->getProjectionEditorWidget().getJoints())[i] == hitJoint){
				hitJointIndex = i;
				break;
			}
		}
	}else{
		for(int i = app->getSurfaceManager()->size() - 1; i >= 0; --i){
			if(app->getSurfaceManager()->getSurface(i)->hitTest(ofVec2f(args.x, args.y))){
				hitSurface = app->getSurfaceManager()->getSurface(i);
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
		_clickPosition = ofVec2f(args.x, args.y); // TODO: redesign this so we can use a kind of
												  //       display stack.
		_bSurfaceDrag = true; // TODO: Should be something like `hitSurface->startDrag()`
		Gui::instance()->notifySurfacePressed(args, hitSurface);
	}else{
		Gui::instance()->notifyBackgroundPressed(args);
	}
}

void ProjectionMappingMode::onMouseReleased(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMouseReleased(args);
	_bSurfaceDrag = false; // TODO: handle this locally
	Gui::instance()->getProjectionEditorWidget().stopDragJoints();
}

void ProjectionMappingMode::onMouseDragged(Application * app, ofMouseEventArgs & args){
	Gui::instance()->onMouseDragged(args);
	Gui::instance()->getProjectionEditorWidget().mouseDragged(args);
	
	// TODO: Handle app->getGui()->clickPosition and app->getGui()->bDrag locally.
	if(_bSurfaceDrag){
		ofVec2f mousePosition = ofVec2f(args.x, args.y);
		ofVec2f distance = mousePosition - _clickPosition;
		Gui::instance()->getProjectionEditorWidget().moveSelectedSurface(distance);
		_clickPosition = mousePosition;
	}
}

void ProjectionMappingMode::onJointPressed(Application * app, GuiJointEvent & e){
	app->getCmdManager()->exec(new SelVertexCmd(app->getSurfaceManager(), e.jointIndex));
	app->getCmdManager()->exec(new MvSurfaceVertCmd(
		e.jointIndex,
		app->getSurfaceManager()->getSelectedSurface()));
}

void ProjectionMappingMode::onSurfacePressed(Application * app, GuiSurfaceEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != e.surface){
		app->getCmdManager()->exec(new SelSurfaceCmd(app->getSurfaceManager(), e.surface ));
	}
	
	app->getCmdManager()->exec(new StartDragSurfaceCmd(e.surface));
}

void ProjectionMappingMode::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	if(app->getSurfaceManager()->getSelectedSurface() != 0){
		app->getCmdManager()->exec(new DeselectSurfaceCmd(app->getSurfaceManager()));
	}
}

void ProjectionMappingMode::onGuiEvent(Application * app, GuiEvent & e){
	
	// Scale widget now. More widgets later.
	if(e.widget == &Gui::instance()->getScaleWidget()){
		if(e.args.type == e.args.Pressed){
			_surfaceScaleBeforeTransform =
				app->getSurfaceManager()->getSelectedSurface()->getScale();
		}else if(e.args.type == e.args.Released){
			if(app->getSurfaceManager()->getSelectedSurface() == 0){
				return;
			}
			
			if(_surfaceScaleBeforeTransform !=
				app->getSurfaceManager()->getSelectedSurface()->getScale()){
				
				app->getCmdManager()->exec(new ScaleSurfaceFromToCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					_surfaceScaleBeforeTransform,
					app->getSurfaceManager()->getSelectedSurface()->getScale()));
			}
		}else if(e.args.type == e.args.Dragged){
			app->getSurfaceManager()->getSelectedSurface()->scaleTo(e.widget->getScale());
		}
	}
}

} // namespace piMapper
} // namespace ofx