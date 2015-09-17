#include "TextureMappingViewState.h"

namespace ofx {
    namespace piMapper {
        
        TextureMappingViewState * TextureMappingViewState::_instance = 0;
    
        TextureMappingViewState * TextureMappingViewState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::TextureMappingViewState();
            }
            return _instance;
        }
        
        void TextureMappingViewState::draw(MainView * mv) {
            ofDrawBitmapString("Texture Mapping View State", 10, 20);
            ofLogNotice("TextureMappingViewState::draw");
        }
    }
}