// SourceSelectionViewState
// Source selection view state singleton
// Created by Krisjanis Rijnieks 2015-09-17
#pragma once

#include "MainView.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
    namespace piMapper {
        
        class SourceSelectionViewState : public ViewState {
            public:
                static SourceSelectionViewState * instance();
                void draw(MainView * mv);
            
            private:
                static SourceSelectionViewState * _instance;
        };
        
    } // namespace piMapper
} // namespace ofx
