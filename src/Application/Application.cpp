#include "Application.h"
#include "PresentationState.h"

namespace ofx {
    namespace piMapper {
        
        Application::Application(ofxPiMapper * opm) {
            _ofxPiMapper = opm;
            setState(PresentationState::instance());
            ofAddListener(ofEvents().keyPressed, this, &Application::onKeyPressed);
        }
        
        Application::~Application() {
            _ofxPiMapper = 0;
            setState(0);
            ofRemoveListener(ofEvents().keyPressed, this, &Application::onKeyPressed);
        }
        
        ApplicationBaseState * Application::getState() {
            return _state;
        }
        
        ofxPiMapper * Application::getOfxPiMapper() {
            return _ofxPiMapper;
        }
        
        void Application::draw(){
            _state->draw(this);
        }
        
        // Here we handle application state changes only
        void Application::onKeyPressed(ofKeyEventArgs & args) {
            
            // For now we set the state of the new system and also the old
            // before it is completely ported to the state system.
            
            switch (args.key) {
                case '1':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, PresentationState::instance(),
                            &_ofxPiMapper->getGui(), GuiMode::NONE));
                    break;
                
                case '2':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, TextureMappingState::instance(),
                            &_ofxPiMapper->getGui(), GuiMode::TEXTURE_MAPPING));
                    break;
                
                case '3':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, ProjectionMappingState::instance(),
                            &_ofxPiMapper->getGui(), GuiMode::PROJECTION_MAPPING));
                    break;
                
                case '4':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, SourceSelectionState::instance(),
                            &_ofxPiMapper->getGui(), GuiMode::SOURCE_SELECTION));
                    break;
                
                case 'f':
                    ofToggleFullscreen();
                    break;
                    
                case 'i':
                    _ofxPiMapper->toggleInfo();
                    break;
    
                case 's':
                    _ofxPiMapper->getSurfaceManager().saveXmlSettings(
                        PIMAPPER_USER_SURFACES_XML_FILE);
                    break;
                
                case 'z':
                    _ofxPiMapper->getCmdManager().undo();
                    break;
                    
                default:
                    // All the other keypresses are handled by the application state onKeyPressed
                    _state->onKeyPressed(this, args);
                    break;
            }
        }
        
        void Application::setState(ApplicationBaseState * st){
            _state = st;
        }
        
    } // namespace piMapper
} // namespace ofx
