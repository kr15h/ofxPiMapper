#include "RemoveSurfaceCommand.h"

namespace ofx{
    namespace piMapper{
        
        RemoveSurfaceCommand::RemoveSurfaceCommand(ofxPiMapper * app){
            _app = app;
            _surface = 0;
        }

        void RemoveSurfaceCommand::exec(){
            // Store the surface, this implies that the surfaceManager's
            // removeSelectedSurface does not destroy the surface.
            _surface = _app->surfaceManager.getSelectedSurface();
            _app->surfaceManager.removeSelectedSurface();
        }
        
        void RemoveSurfaceCommand::undo(){
            ofLogNotice("RemoveSurfaceCommand", "undo");
            if (_surface == 0) {
                ofLogError("RemoveSurfaceCommand", "No surface stored");
            }
            _app->surfaceManager.addSurface(_surface);
            _surface = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

