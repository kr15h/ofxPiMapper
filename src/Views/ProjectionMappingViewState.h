// ProejectionMappingViewState
// Projection mapping view state singleton
// Created by Krisjanis Rijnieks 2015-09-17
#pragma once

#include "MainView.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
    namespace piMapper {
        
        class ProjectionMappingViewState : public ViewState {
            public:
                static ProjectionMappingViewState * instance();
                void draw(MainView * mv);
            
            private:
                static ProjectionMappingViewState * _instance;
        };
        
    } // namespace piMapper
} // namespace ofx
