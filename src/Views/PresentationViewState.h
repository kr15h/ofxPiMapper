// PresentationViewState
// Presentation view state singleton
// Created by Krisjanis Rijnieks 2015-05-24
#pragma once

#include "MainView.h"
#include "ViewState.h"
#include "ofEvents.h"
#include "ofLog.h"

class MainView;

namespace ofx {
    namespace piMapper {
        class PresentationViewState : public ViewState {
            public:
                static ViewState * instance();
                void mousePressed(ofMouseEventArgs & args);
            
            protected:
                PresentationViewState();
            
            private:
                static ViewState * _instance;
        };
    }
}