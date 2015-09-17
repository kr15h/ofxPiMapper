// MainView
// Main entrance point for the visible part of this application
// Created by Krisjanis Rijnieks 2015-05-22
#pragma once

#include "ofEvents.h"
#include "ofLog.h"
#include "ViewState.h"

namespace ofx {
    namespace piMapper {
        
        class ViewState;
    
        class MainView {
            public:
                MainView();
                void draw();
            
            protected:
                void setState(ViewState * st);
            
            private:
                friend class ViewState;
                ViewState * _state;
        };
        
    } // namespace piMapper
} // namespace ofx
