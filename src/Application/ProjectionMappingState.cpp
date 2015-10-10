#include "ProjectionMappingState.h"

namespace ofx {
    namespace piMapper {
        
        ProjectionMappingState * ProjectionMappingState::_instance = 0;
    
        ProjectionMappingState * ProjectionMappingState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::ProjectionMappingState();
            }
            return _instance;
        }
        
        void ProjectionMappingState::draw(Application * app) {
            ofDrawBitmapString("Projection Mapping State", 10, 20);
        }
    }
}