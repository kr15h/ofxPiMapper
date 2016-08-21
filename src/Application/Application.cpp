#include "Application.h"
#include "PresentationState.h"

namespace ofx {
namespace piMapper {

Application::Application(){
	_surfaceManager.setMediaServer(&_mediaServer);
	_gui.setMediaServer(&_mediaServer);
	_gui.setCmdManager(&_cmdManager);
	_gui.setSurfaceManager(&_surfaceManager);
	
	setState(PresentationState::instance());
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
	if(!loadXmlSettings(PIMAPPER_USER_SURFACES_XML_FILE)){
		ofLogWarning("Application::setup()") << "Failed to load user settings" << endl;
		if(!loadXmlSettings(PIMAPPER_DEF_SURFACES_XML_FILE)){
			ofLogWarning("Application::setup()") << "Failed to load default settings" << endl;
		}
	}
	
    if(_isSSHConnection){
        consoleListener.setup(this);
    }
}

ApplicationBaseState * Application::getState(){
	return _state;
}

void Application::draw(){
	_state->draw(this);
	_info.draw();
}

// Here we handle application state changes only
void Application::onKeyPressed(ofKeyEventArgs & args){

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
			 new ofx::piMapper::SetApplicationStateCmd(
				 this, PresentationState::instance(),
				 &_gui, GuiMode::NONE));
		 break;

	 case '2':
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationStateCmd(
				 this, TextureMappingState::instance(),
				 &_gui, GuiMode::TEXTURE_MAPPING));
		 break;

	 case '3':
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationStateCmd(
				 this, ProjectionMappingState::instance(),
				 &_gui, GuiMode::PROJECTION_MAPPING));
		 break;

	 case '4':
		 _cmdManager.exec(
			 new ofx::piMapper::SetApplicationStateCmd(
				 this, SourceSelectionState::instance(),
				 &_gui, GuiMode::SOURCE_SELECTION));
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
	if(e.widget == &Gui::instance()->getScaleWidget()){
		if(e.args.type == e.args.Pressed){
			cout << "Scale Pressed" << endl;
		}else if(e.args.type == e.args.Released){
			cout << "Scale Released" << endl;
		}else if(e.args.type == e.args.Dragged){
			cout << "Scale Dragged" << endl;
		}
	}
}

void Application::addFboSource(FboSource & fboSource){
	_mediaServer.addFboSource(fboSource);
}

void Application::addFboSource(FboSource * fboSource){
	_mediaServer.addFboSource(fboSource);
}

void Application::setState(ApplicationBaseState * st){
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
