#pragma once

#include "ofEvents.h"
#include "ofLog.h"
#include "ApplicationBaseState.h"

namespace ofx {
    namespace piMapper {
        
        class ApplicationBaseState;
    
        class Application {
            public:
                Application();
                void draw();
            
            protected:
                void setState(ApplicationBaseState * st);
            
            private:
                friend class ApplicationBaseState;
                ApplicationBaseState * _state;
        };
        
    } // namespace piMapper
} // namespace ofx
