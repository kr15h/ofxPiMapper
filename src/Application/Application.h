#pragma once

#include "ofEvents.h"
#include "ofLog.h"

#include "ofxPiMapper.h"
#include "SetApplicationStateCmd.h"
#include "ApplicationBaseState.h"
#include "PresentationState.h"
#include "ProjectionMappingState.h"
#include "TextureMappingState.h"
#include "SourceSelectionState.h"

class ofxPiMapper;

namespace ofx {
    namespace piMapper {
        
        class ApplicationBaseState;
    
        class Application {
            public:
                Application(ofxPiMapper * opm);
                ~Application();
            
                ApplicationBaseState * getState();
            
                void draw();
                void onKeyPressed(ofKeyEventArgs & args);
            
            protected:
                void setState(ApplicationBaseState * st);
            
            private:
                friend class ApplicationBaseState;
                friend class SetApplicationStateCmd;
            
                ApplicationBaseState * _state;
                ofxPiMapper * _ofxPiMapper;
        };
        
    } // namespace piMapper
} // namespace ofx
