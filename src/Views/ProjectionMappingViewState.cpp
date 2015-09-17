#include "ProjectionMappingViewState.h"

namespace ofx {
    namespace piMapper {
        
        ProjectionMappingViewState * ProjectionMappingViewState::_instance = 0;
    
        ProjectionMappingViewState * ProjectionMappingViewState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::ProjectionMappingViewState();
            }
            return _instance;
        }
        
        void ProjectionMappingViewState::draw(MainView * mv) {
            ofDrawBitmapString("Projection Mapping View State", 10, 20);
            ofLogNotice("ProjectionMappingViewState::draw");
        }
    }
}