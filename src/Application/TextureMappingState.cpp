#include "TextureMappingState.h"

namespace ofx {
    namespace piMapper {
        
        TextureMappingState * TextureMappingState::_instance = 0;
    
        TextureMappingState * TextureMappingState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::TextureMappingState();
            }
            return _instance;
        }
        
        void TextureMappingState::draw(Application * app) {
            ofDrawBitmapString("Texture Mapping State", 10, 20);
        }
    }
}