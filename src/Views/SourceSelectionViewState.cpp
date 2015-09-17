#include "SourceSelectionViewState.h"

namespace ofx {
    namespace piMapper {
        
        SourceSelectionViewState * SourceSelectionViewState::_instance = 0;
    
        SourceSelectionViewState * SourceSelectionViewState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::SourceSelectionViewState();
            }
            return _instance;
        }
        
        void SourceSelectionViewState::draw(MainView * mv) {
            ofDrawBitmapString("Source Selection View State", 10, 20);
            ofLogNotice("SourceSelectionViewState::draw");
        }
    }
}