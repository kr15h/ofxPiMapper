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
}

void Application::setup(){
	if(!loadXmlSettings(PIMAPPER_USER_SURFACES_XML_FILE)){
		ofLogWarning("Application::setup()") << "Failed to load user settings" << endl;
		if(!loadXmlSettings(PIMAPPER_DEF_SURFACES_XML_FILE)){
			ofLogWarning("Application::setup()") << "Failed to load default settings" << endl;
		}
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
		 _surfaceManager.saveXmlSettings(
			 PIMAPPER_USER_SURFACES_XML_FILE);
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

void Application::addFboSource(FboSource & fboSource){
	_mediaServer.addFboSource(fboSource);
}

void Application::setState(ApplicationBaseState * st){
	_state = st;
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

} // namespace piMapper
} // namespace ofx
