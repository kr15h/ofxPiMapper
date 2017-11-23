#include "Application.h"
#include "PresentationMode.h"

namespace ofx {
namespace piMapper {

Application::Application(){
	_keySequence = "";
	_surfaceManager.setMediaServer(&_mediaServer);

	// Set initial mode
	setState(PresentationMode::instance());
	ofHideCursor();

	ofAddListener(Gui::instance()->jointPressedEvent, this, &Application::onJointPressed);
	ofAddListener(Gui::instance()->surfacePressedEvent, this, &Application::onSurfacePressed);
	ofAddListener(Gui::instance()->backgroundPressedEvent, this, &Application::onBackgroundPressed);
	ofAddListener(Gui::instance()->guiEvent, this, &Application::onGuiEvent);

	_lastSaveTime = 0.0f;
	_autoSaveInterval = 60.0f;
}

void Application::setup(){
	// Setup components
	_mediaServer.setup();

	if(!loadXmlSettings(PIMAPPER_SETTINGS_FILE)){
		if(SettingsLoader::instance()->create(PIMAPPER_SETTINGS_FILE)){
			bool success = loadXmlSettings(PIMAPPER_SETTINGS_FILE);
			if(!success){
				throw runtime_error("ofxPiMapper: Failed to load settings.");
			}
		}else{
			throw runtime_error("ofxPiMapper: Failed to create default settings file.");
		}
	}

	// Setup all states.
	PresentationMode::instance()->setup(this);
	TextureMappingMode::instance()->setup(this);
	ProjectionMappingMode::instance()->setup(this);
	SourceSelectionMode::instance()->setup(this);

	// TODO: Consider whether this is the right place for it
	Gui::instance()->getScaleWidget().setSurfaceManager(&_surfaceManager);
}

void Application::update(){
	_mediaServer.update();
	_state->update(this);

	// Autosave, do it only of the mode is not presentation mode
	if(_state != PresentationMode::instance()){
		float timeNow = ofGetElapsedTimef();
		if(timeNow - _lastSaveTime > _autoSaveInterval){
			saveProject();
			_lastSaveTime = timeNow;
		}
	}
}

ApplicationBaseMode * Application::getState(){
	return _state;
}

void Application::draw(){
	_mediaServer.draw();
	_state->draw(this);
	_info.draw();
}

// Here we handle application state changes only
void Application::onKeyPressed(ofKeyEventArgs & args){

	// Key sequence based commands. Last three keys are taken into account.
	_keySequence += args.key;
	if(_keySequence.size() >= 3){
		_keySequence = _keySequence.substr(_keySequence.size() - 3, 3);
		if(_keySequence == "new"){
			if(_surfaceManager.getActivePreset()->size()){
				_cmdManager.exec(new ClearSurfacesCmd(getSurfaceManager()));
			}
			return;
		}else if(_keySequence == "rbt"){
			reboot();
			return;
		}else if(_keySequence == "sdn"){
			shutdown();
			return;
		}else if(_keySequence == "ext"){
			exit(0);
		}
	}

	// For now we set the state of the new system and also the old
	// before it is completely ported to the state system.

	switch(args.key){
	 case OF_KEY_SHIFT:
		 _shiftKeyDown = true;
		 break;

	 case '/':
		 _shiftKeyDown = !_shiftKeyDown;
		 break;

	 case '1':
		 setPresentationMode();
		 break;

	 case '2':
		 setTextureMode();
		 break;

	 case '3':
		 setProjectionMode();
		 break;

	 case '4':
		 setSourceMode();
		 break;

	 case 'i':
		 toggleInfo();
		 break;

	 case 's':
		 saveProject();
		 break;

	 case 'z':
		 undo();
		 break;

	 case 'n':
		 setNextPreset();
		 break;

	 default:
		 // All the other keypresses are handled by the application state onKeyPressed
		 _state->onKeyPressed(this, args);
		 break;
	}
}

void Application::onKeyReleased(ofKeyEventArgs & args){
	switch(args.key){
	 case OF_KEY_SHIFT:
		_shiftKeyDown = false;
		break;
	}
}

void Application::onMousePressed(ofMouseEventArgs & args){
    _state->onMousePressed(this, args);
}

void Application::onMouseReleased(ofMouseEventArgs & args){
	_state->onMouseReleased(this, args);
}

void Application::onMouseDragged(ofMouseEventArgs &args){
	_state->onMouseDragged(this, args);
}

void Application::onJointPressed(GuiJointEvent & e){
	_state->onJointPressed(this, e);
}

void Application::onSurfacePressed(GuiSurfaceEvent & e){
	_state->onSurfacePressed(this, e);
}

void Application::onBackgroundPressed(GuiBackgroundEvent & e){
	_state->onBackgroundPressed(this, e);
}

void Application::onGuiEvent(GuiEvent & e){
	_state->onGuiEvent(this, e);
}

void Application::addFboSource(FboSource & fboSource){
	_mediaServer.addFboSource(fboSource);
}

void Application::addFboSource(FboSource * fboSource){
	_mediaServer.addFboSource(fboSource);
}

void Application::createSurface(SurfaceType type){
	getCmdManager()->exec(
		new AddSurfaceCmd(getSurfaceManager(), type));
}

void Application::eraseSurface(int i){
	if(i >= 0 && i < getSurfaceManager()->getActivePreset()->getSurfaces().size()){
		getCmdManager()->exec(new RmSurfaceCmd(getSurfaceManager(), i));
	}
}

void Application::setInfoText(string text){
	_info.setText(text);
}

void Application::toggleInfo(){
	_info.toggle();
}

void Application::togglePerspective(){
	if(getSurfaceManager()->getSelectedSurface() == 0){
		return;
	}

	if(getSurfaceManager()->getSelectedSurface()->getType() == SurfaceType::QUAD_SURFACE){
		getCmdManager()->exec(new TogglePerspectiveCmd(
		 (QuadSurface *)getSurfaceManager()->getSelectedSurface()));
	}
}

void Application::saveProject(){
	ofLogNotice("Application::saveProject", "Saving project...");
	_surfaceManager.saveXmlSettings(SettingsLoader::instance()->getLastLoadedFilename());
}

void Application::setState(ApplicationBaseMode * st){
	_state = st;
}

bool Application::isShiftKeyDown(){
	return _shiftKeyDown;
}

void Application::setPreset(unsigned int i){
	_cmdManager.exec(new SetPresetCmd(this, i));
}

void Application::setNextPreset(){
	unsigned int numPresets = _surfaceManager.getNumPresets();
	if(numPresets <= 1){
		return;
	}
	int activePreset = _surfaceManager.getActivePresetIndex();
	if(activePreset >= numPresets - 1){
		activePreset = 0;
	}else{
		activePreset += 1;
	}
	setPreset(activePreset);
}

void Application::reboot(){
	#ifdef TARGET_RASPBERRY_PI
		system("sudo shutdown -r now");
	#else
		ofLogNotice("Application::reboot()", "Supported only on Raspberry Pi");
	#endif
}

void Application::shutdown(){
	#ifdef TARGET_RASPBERRY_PI
		system("sudo shutdown -h now");
	#else
		ofLogNotice("Application::shutdown()", "Supported only on Raspberry Pi");
	#endif
}

bool Application::loadXmlSettings(string fileName){
	if(!ofFile::doesFileExist(fileName)){
		ofLogError("Application::loadXmlSettings()") << fileName << " does not exist";
		return false;
	}
	if(!_surfaceManager.loadXmlSettings(fileName)){
		ofLogError("Application::loadXmlSettings()") << "Failed to load " << fileName << endl;
		return false;
	}
	return true;
}

void Application::selectSurface(int i){
	if(getSurfaceManager()->size()){
		if(getSurfaceManager()->getSelectedSurfaceIndex() == i){
			return;
		}
		getCmdManager()->exec(
		 new SelSurfaceCmd(
		  getSurfaceManager(),
		  getSurfaceManager()->getSurface(i)));
	}
}

void Application::selectNextSurface(){
	if(getSurfaceManager()->size()){
		if(getSurfaceManager()->size() == 1 &&
		 getSurfaceManager()->getSelectedSurface() ==
		 getSurfaceManager()->getSurface(0)){
			return;
		}
		getCmdManager()->exec(new SelNextSurfaceCmd(getSurfaceManager()));
	}
}

void Application::selectPrevSurface(){
	if(getSurfaceManager()->size()){
		if(getSurfaceManager()->size() == 1 &&
		 getSurfaceManager()->getSelectedSurface() ==
		 getSurfaceManager()->getSurface(0)){
			return;
		}
		getCmdManager()->exec(new SelPrevSurfaceCmd(getSurfaceManager()));
	}
}

void Application::selectNextVertex(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(new SelNextVertexCmd(getSurfaceManager()));
	}
}

void Application::selectPrevVertex(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(new SelPrevVertexCmd(getSurfaceManager()));
	}
}

void Application::selectVertex(int surface, int vertex){
	if(getSurfaceManager()->size()){

		// TODO: use one command instead of two

		getCmdManager()->exec(
		 new SelSurfaceCmd(
		  getSurfaceManager(),
		  getSurfaceManager()->getSurface(surface)));

		getCmdManager()->exec(
		 new SelVertexCmd(
		  getSurfaceManager(),
		  vertex));
	}
}

void Application::selectNextTexCoord(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(
		 new SelNextTexCoordCmd(
		  &Gui::instance()->getTextureEditorWidget()));
	}
}

void Application::selectPrevTexCoord(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(
		 new SelPrevTexCoordCmd(
		  &Gui::instance()->getTextureEditorWidget()));
	}
}

void Application::moveSelection(ofVec2f by){
	if(_state == ProjectionMappingMode::instance()){
		getCmdManager()->exec(new MvSelectionCmd(getSurfaceManager(), by));
	}else if(_state == TextureMappingMode::instance()){
		int selectedTexCoord = Gui::instance()->getTextureEditorWidget().getSelectedTexCoord();
		if(selectedTexCoord >= 0){
			moveTexCoord(selectedTexCoord, by);
		}
	}
}

void Application::setPresentationMode(){
	_cmdManager.exec(
		new ofx::piMapper::SetApplicationModeCmd(
			this, PresentationMode::instance()));
}

void Application::setTextureMode(){
	_cmdManager.exec(
		new ofx::piMapper::SetApplicationModeCmd(
			this, TextureMappingMode::instance()));
}

void Application::setProjectionMode(){
	_cmdManager.exec(
		new ofx::piMapper::SetApplicationModeCmd(
			this, ProjectionMappingMode::instance()));
}

void Application::setSourceMode(){
	_cmdManager.exec(
		new ofx::piMapper::SetApplicationModeCmd(
			this, SourceSelectionMode::instance()));
}

void Application::moveLayerUp(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface() ==
		 getSurfaceManager()->getActivePreset()->at(
		 getSurfaceManager()->getActivePreset()->size() - 1)){
			return;
		}

		getCmdManager()->exec(
		 new MvLayerUpCmd(
		  getSurfaceManager()->getActivePreset(),
		  getSurfaceManager()->getSelectedSurface()));
	}
}

void Application::moveLayerDown(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface() ==
		 getSurfaceManager()->getActivePreset()->at(0)){
			return;
		}

		getCmdManager()->exec(
		 new MvLayerDnCmd(
		  getSurfaceManager()->getActivePreset(),
		  getSurfaceManager()->getSelectedSurface()));
	}
}

void Application::scaleUp(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(
		 new ScaleSurfaceFromToCmd(
		  getSurfaceManager()->getSelectedSurface(),
		  getSurfaceManager()->getSelectedSurface()->getScale(),
		  getSurfaceManager()->getSelectedSurface()->getScale() + 0.2f));
	}
}

void Application::scaleDown(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface()->getScale() <= 0.21f){
			return;
		}
		getCmdManager()->exec(
		 new ScaleSurfaceFromToCmd(
		  getSurfaceManager()->getSelectedSurface(),
		  getSurfaceManager()->getSelectedSurface()->getScale(),
		  getSurfaceManager()->getSelectedSurface()->getScale() - 0.2f));
	}
}

void Application::duplicateSurface(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(
		 new DuplicateSurfaceCmd(
		  getSurfaceManager()->getSelectedSurface(),
		  getSurfaceManager()));
	}
}

void Application::setNextSource(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(
		 new SetNextSourceCmd(
		  getSurfaceManager()->getSelectedSurface(),
		  &Gui::instance()->getSourcesEditorWidget()));
	}else{
		getCmdManager()->exec(new SelNextSurfaceCmd(getSurfaceManager()));
	}
}

void Application::setFboSource(string sourceId){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(
		 new SetSourceCmd(
			SourceType::SOURCE_TYPE_FBO,
			sourceId,
		  getSurfaceManager()->getSelectedSurface(),
		  &Gui::instance()->getSourcesEditorWidget()));
	}else{
		getCmdManager()->exec(new SelNextSurfaceCmd(getSurfaceManager()));
	}
}

void Application::addGridRow(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface()->getType() ==
		 SurfaceType::GRID_WARP_SURFACE){
			// TODO: The command should not require projection editor pointer
			getCmdManager()->exec(
			 new AddGridRowCmd(
			  (GridWarpSurface *)getSurfaceManager()->getSelectedSurface() ));
		}
	}
}

void Application::addGridColumn(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface()->getType() ==
		 SurfaceType::GRID_WARP_SURFACE){
			// TODO: The command should not require projection editor pointer
			getCmdManager()->exec(
			 new AddGridColCmd(
			  (GridWarpSurface *)getSurfaceManager()->getSelectedSurface() ));
		}
	}
}

void Application::removeGridRow(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface()->getType() ==
		 SurfaceType::GRID_WARP_SURFACE){
			if(((GridWarpSurface *)getSurfaceManager()->getSelectedSurface())->getGridRows() > 1){
				// TODO: The command should not require projection editor pointer
				getCmdManager()->exec(
				 new RmGridRowCmd(
				  (GridWarpSurface *)getSurfaceManager()->getSelectedSurface() ));
			}
		}
	}
}

void Application::removeGridColumn(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		if(getSurfaceManager()->getSelectedSurface()->getType() ==
		 SurfaceType::GRID_WARP_SURFACE){
			if(((GridWarpSurface *)getSurfaceManager()->getSelectedSurface())->getGridCols() > 1){
				// TODO: The command should not require projection editor pointer
				getCmdManager()->exec(
				 new RmGridColCmd(
				  (GridWarpSurface *)getSurfaceManager()->getSelectedSurface() ));
			}
		}
	}
}

void Application::togglePause(){
	if(getSurfaceManager()->getSelectedSurface() == 0){
		return;
	}

	if(getSurfaceManager()->getSelectedSurface()->getSource()->getType() ==
	 SourceType::SOURCE_TYPE_VIDEO){
		getCmdManager()->exec(
		 new ToggleAnimatedSourceCmd(
		  getSurfaceManager()->getSelectedSurface()));
	}
}

void Application::moveTexCoord(int texCoordIndex, ofVec2f by){
	if(texCoordIndex >= 0){
		getCmdManager()->exec(new MvTexCoordCmd(texCoordIndex, by));
	}else{
		getCmdManager()->exec(new MvAllTexCoordsCmd(
		 getSurfaceManager()->getSelectedSurface(),
		 &Gui::instance()->getTextureEditorWidget()));

		Gui::instance()->getTextureEditorWidget().moveSelection(by);
	}
}

void Application::undo(){
	_cmdManager.undo();
}

void Application::deselect(){
	if(getSurfaceManager()->getSelectedSurface() != 0){
		getCmdManager()->exec(new DeselectSurfaceCmd(getSurfaceManager()));
	}
}

} // namespace piMapper
} // namespace ofx
