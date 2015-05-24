// ViewState
// Base class for main view states
// Created by Krisjanis Rijnieks 2015-05-22
#pragma once

#include "MainView.h"
#include "ofEvents.h"

class MainView;

namespace ofx {
    namespace piMapper {
        class ViewState {
            public:
                virtual void mousePressed(ofMouseEventArgs & args);
            
            protected:
                void setState(MainView * view, ViewState * state);
        };
    }
}