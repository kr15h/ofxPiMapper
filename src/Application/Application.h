#pragma once

#include "ofEvents.h"
#include "ofLog.h"
#include "ApplicationBaseState.h"
#include "ofxPiMapper.h"

class ofxPiMapper;

namespace ofx {
    namespace piMapper {
        
        class ApplicationBaseState;
    
        class Application {
            public:
                Application(ofxPiMapper * opm);
                ~Application();
            
                void draw();
                void onKeyPressed(ofKeyEventArgs & args);
            
            protected:
                void setState(ApplicationBaseState * st);
            
            private:
                friend class ApplicationBaseState;
                ApplicationBaseState * _state;
                ofxPiMapper * _ofxPiMapper;
        };
        
    } // namespace piMapper
} // namespace ofx
