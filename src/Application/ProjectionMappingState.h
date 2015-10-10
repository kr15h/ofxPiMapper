#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
    namespace piMapper {
        
        class ProjectionMappingState : public ApplicationBaseState {
            public:
                static ProjectionMappingState * instance();
                void draw(Application * app);
            
            private:
                static ProjectionMappingState * _instance;
        };
        
    } // namespace piMapper
} // namespace ofx
