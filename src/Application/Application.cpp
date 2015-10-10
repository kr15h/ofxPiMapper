#include "Application.h"
#include "PresentationState.h"

namespace ofx {
    namespace piMapper {
        
        Application::Application(){
            setState(PresentationState::instance());
        }
        
        void Application::draw(){
            _state->draw(this);
        }
        
        void Application::setState(ApplicationBaseState * st){
            _state = st;
        }
        
    } // namespace piMapper
} // namespace ofx
