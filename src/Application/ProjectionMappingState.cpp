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
        
        void ProjectionMappingState::draw(Application * app) {}
        
        void ProjectionMappingState::onKeyPressed(Application * app, ofKeyEventArgs & args) {
            switch (args.key) {
                
                case 't':
                    app->getOfxPiMapper()->getCmdManager().exec(
                        new AddSurfaceCmd(
                            app->getOfxPiMapper(),
                            SurfaceType::TRIANGLE_SURFACE)
                    );
                    break;
                    
                case 'q':
                    app->getOfxPiMapper()->getCmdManager().exec(
                        new AddSurfaceCmd(
                            app->getOfxPiMapper(),
                            SurfaceType::QUAD_SURFACE)
                    );
                    break;
                    
                case OF_KEY_BACKSPACE:
                    app->getOfxPiMapper()->getCmdManager().exec(
                        new RmSurfaceCmd(app->getOfxPiMapper()));
                    break;
                
                default:
                    break;
            }
        }
    }
}