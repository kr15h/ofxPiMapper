// Keyboard
// Keyboard input handler
// Creates commands on keyboard input and forwards them to the CommandManager
// Created by Krisjanis Rijnieks on 2015-09-17
#pragma once

#include "ofEvents.h"
#include "ofEventUtils.h"
#include "ofLog.h"
#include "ofxPiMapper.h"
#include "SetGuiModeCmd.h"
#include "GuiMode.h"

class ofxPiMapper;

namespace ofx {
    namespace piMapper {
    
        class Keyboard {
            public:
                Keyboard(ofxPiMapper * opm);
                ~Keyboard();
            
                void onKeyPressed(ofKeyEventArgs & args);
            
            private:
                ofxPiMapper * _ofxPiMapper;
        };
    
    }
}