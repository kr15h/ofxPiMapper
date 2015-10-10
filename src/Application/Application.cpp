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
        
        void Application::draw(){
            _state->draw(this);
        }
        
        // Here we handle application state changes only
        void Application::onKeyPressed(ofKeyEventArgs & args) {
            switch (args.key) {
                case '1':
                    ofLogNotice("Application::onKeyPressed()") << "Switching to Presentation State";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::NONE) {
                        _ofxPiMapper->getCmdManager().exec(
                            new ofx::piMapper::SetGuiModeCmd(&_ofxPiMapper->getGui(),
                            ofx::piMapper::GuiMode::NONE));
                    }
                    break;
                case '2':
                    ofLogNotice("Application::onKeyPressed()") << "Switching to Projection Mapping State";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::PROJECTION_MAPPING) {
                        _ofxPiMapper->getCmdManager().exec(
                            new ofx::piMapper::SetGuiModeCmd(&_ofxPiMapper->getGui(),
                            ofx::piMapper::GuiMode::PROJECTION_MAPPING));
                    }
                    break;
                case '3':
                    ofLogNotice("Application::onKeyPressed()") << "Switching to Source Selection State";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::SOURCE_SELECTION) {
                        _ofxPiMapper->getCmdManager().exec(
                            new ofx::piMapper::SetGuiModeCmd(&_ofxPiMapper->getGui(),
                            ofx::piMapper::GuiMode::SOURCE_SELECTION));
                    }
                    break;
                case '4':
                    ofLogNotice("Application::onKeyPressed()") << "Switching to Texture Mapping State";
                    if (_ofxPiMapper->getGui().getMode() != ofx::piMapper::GuiMode::TEXTURE_MAPPING) {
                        _ofxPiMapper->getCmdManager().exec(
                            new ofx::piMapper::SetGuiModeCmd(&_ofxPiMapper->getGui(),
                            ofx::piMapper::GuiMode::TEXTURE_MAPPING));
                    }
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
