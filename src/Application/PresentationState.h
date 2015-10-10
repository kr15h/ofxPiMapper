#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
    namespace piMapper {
        
        class PresentationState : public ApplicationBaseState {
            public:
                static PresentationState * instance();
                void draw(Application * app);
            
            private:
                static PresentationState * _instance;
        };
        
    } // namespace piMapper
} // namespace ofx
