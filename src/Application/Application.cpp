#include "Application.h"
#include "PresentationMode.h"

namespace ofx {
namespace piMapper {

Application::Application(){
	_keySequence = "";

	_surfaceManager.setMediaServer(&_mediaServer);
	
	setState(PresentationMode::instance());
	
	ofAddListener(ofEvents().keyPressed, this, &Application::onKeyPressed);
	ofAddListener(ofEvents().keyReleased, this, &Application::onKeyReleased);
	ofAddListener(ofEvents().mousePressed, this, &Application::onMousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &Application::onMouseReleased);
	ofAddListener(ofEvents().mouseDragged, this, &Application::onMouseDragged);
	
	ofAddListener(Gui::instance()->jointPressedEvent, this, &Application::onJointPressed);
	ofAddListener(Gui::instance()->surfacePressedEvent, this, &Application::onSurfacePressed);
	ofAddListener(Gui::instance()->backgroundPressedEvent, this, &Application::onBackgroundPressed);
	
	ofAddListener(Gui::instance()->guiEvent, this, &Application::onGuiEvent);
    
    string SSHConnection = ofSystem("if [ -z $SSH_CONNECTION ]; then echo no; else echo yes; fi");
    if(SSHConnection == "yes"){
        _isSSHConnection = true;
    }else{
        _isSSHConnection = false;
    }
}

void Application::setup(){
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
	
    if(_isSSHConnection){
        consoleListener.setup(this);
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
	_state->update(this);
}

ApplicationBaseMode * Application::getState(){
	return _state;
}

void Application::draw(){
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
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationModeCmd(
				 this, PresentationMode::instance()));
		 break;

	 case '2':
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationModeCmd(
				 this, TextureMappingMode::instance()));
		 break;

	 case '3':
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationModeCmd(
				 this, ProjectionMappingMode::instance()));
		 break;

	 case '4':
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationModeCmd(
				 this, SourceSelectionMode::instance()));
		 break;

	 case 'f':
		 ofToggleFullscreen();
		 break;

	 case 'i':
		 _info.toggle();
		 break;

	 case 's':
		 _surfaceManager.saveXmlSettings(SettingsLoader::instance()->getLastLoadedFilename());
		 break;

	 case 'z':
		 _cmdManager.undo();
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

void Application::setState(ApplicationBaseMode * st){
	_state = st;
}

bool Application::isShiftKeyDown(){
	return _shiftKeyDown;
}

void Application::onCharacterReceived(KeyListenerEventData & e){
    ofKeyEventArgs args;
	args.key = (int)e.character;
	
	// These if's have been added because we get
	// capital letters A, B, C and D when pressing
	// arrows on the keyboard via terminal.
	
	switch(args.key){
	 case 'A':
		args.key = OF_KEY_UP;
		break;
	 case 'B':
		args.key = OF_KEY_DOWN;
		break;
	 case 'C':
		args.key = OF_KEY_RIGHT;
		break;
	 case 'D':
		args.key = OF_KEY_LEFT;
		break;
	 case '\\':
		args.key = OF_KEY_BACKSPACE;
		break;
	}
	
	cout << "TermListener: " << e.character << endl;
	onKeyPressed(args);
};

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

} // namespace piMapper
} // namespace ofx
