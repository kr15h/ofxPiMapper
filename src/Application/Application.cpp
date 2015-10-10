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
        
        void Application::draw(){
            _state->draw(this);
        }
        
        // Here we handle application state changes only
        void Application::onKeyPressed(ofKeyEventArgs & args) {
            switch (args.key) {
                case '1':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, PresentationState::instance()));
                    break;
                case '2':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, TextureMappingState::instance()));
                    break;
                case '3':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, ProjectionMappingState::instance()));
                    break;
                case '4':
                    _ofxPiMapper->getCmdManager().exec(
                        new ofx::piMapper::SetApplicationStateCmd(
                            this, SourceSelectionState::instance()));
                    break;
                default:
                    break;
            }
        }
        
        void Application::setState(ApplicationBaseState * st){
            _state = st;
        }
        
    } // namespace piMapper
} // namespace ofx
