// MainView
// Main entrance point for the visible part of this application
// Created by Krisjanis Rijnieks 2015-05-22
#pragma once

#include "ViewState.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "PresentationViewState.h"

class ViewState;

namespace ofx {
    namespace piMapper {
        class MainView {
            public:
                MainView();
                void mousePressed(ofMouseEventArgs & args);
            
            private:
                friend class ViewState;
                void setState(ofx::piMapper::ViewState * state);
            
            private:
                ViewState * _state;
        };
    }
}