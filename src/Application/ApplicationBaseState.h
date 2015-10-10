#pragma once

#include "ofEvents.h"
#include "ofLog.h"

namespace ofx {
    namespace piMapper {
        
        class Application;
        
        class ApplicationBaseState {
            public:
                virtual void draw(Application * app){};
                virtual void setState(Application * app, ApplicationBaseState * st);
            
                // Event handler virtual methods
                virtual void keyPressed(){};
        };
        
    } // namespace piMapper
} // namespace ofx
