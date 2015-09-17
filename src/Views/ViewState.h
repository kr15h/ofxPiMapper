// ViewState
// Base class for view states
// Created by Krisjanis Rijnieks 2015-06-03
#pragma once

#include "ofEvents.h"
#include "ofLog.h"

namespace ofx {
    namespace piMapper {
        
        class MainView;
        
        class ViewState {
            public:
                virtual void draw(MainView * mv){};
                virtual void setState(MainView * mainView, ViewState * state);
        };
        
    } // namespace piMapper
} // namespace ofx
