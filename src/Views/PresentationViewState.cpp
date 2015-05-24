#include "PresentationViewState.h"

namespace ofx {
    namespace piMapper {
        ViewState * PresentationViewState::_instance = 0;
    
        ViewState * PresentationViewState::instance() {
            if (_instance == 0) {
                _instance = new PresentationViewState();
            }
            return _instance;
        }
        
        void PresentationViewState::mousePressed(ofMouseEventArgs & args) {
            ofLogNotice("PresentationViewState::mousePressed")
                << "x: " << args.x
                << ", y: " << args.y;
        }
    }
}