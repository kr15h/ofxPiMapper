#include "PresentationViewState.h"

namespace ofx {
    namespace piMapper {
        
        PresentationViewState * PresentationViewState::_instance = 0;
    
        PresentationViewState * PresentationViewState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::PresentationViewState();
            }
            return _instance;
        }
        
        void PresentationViewState::draw(MainView * mv) {
            ofSetColor(255, 255, 0);
            ofDrawBitmapString("Presentation View State", 10, 20);
            //ofLogNotice("PresentationViewState::draw");
        }
    }
}