#include "MoveSurfaceCommand.h"

namespace ofx{
    namespace piMapper{
        
        MoveSurfaceCommand::MoveSurfaceCommand(
            BaseSurface * surface,
            ProjectionEditor * projectionEditor){
            
            _surface = surface;
            _projectionEditor = projectionEditor;
        }

        void MoveSurfaceCommand::exec(){
            ofLogNotice("MoveSurfaceCommand", "exec");
            _previousVertices = _surface->getVertices();
            _surface->setMoved(false);
        }
        
        void MoveSurfaceCommand::undo(){
            ofLogNotice("MoveSurfaceCommand", "undo");
            _surface->moveBy(_previousVertices[0] - _surface->getVertices()[0]);
            _projectionEditor->updateJoints();
            _previousVertices.clear();
            _surface = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

