// TextureMappingViewState
// Texture mapping view state singleton
// Created by Krisjanis Rijnieks 2015-09-17
#pragma once

#include "MainView.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
    namespace piMapper {
        
        class TextureMappingViewState : public ViewState {
            public:
                static TextureMappingViewState * instance();
                void draw(MainView * mv);
            
            private:
                static TextureMappingViewState * _instance;
        };
        
    } // namespace piMapper
} // namespace ofx
