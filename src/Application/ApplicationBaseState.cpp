#include "ApplicationBaseState.h"
#include "PresentationState.h"

namespace ofx {
    namespace piMapper {
    
        void ApplicationBaseState::setState(Application * app, ApplicationBaseState * st) {
            app->setState(st);
        }
        
    } // namespace piMapper
} // namespace ofx
