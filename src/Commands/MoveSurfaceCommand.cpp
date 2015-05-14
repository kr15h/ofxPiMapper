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
            // Store surface location by copying vertices
            _previousVertices = _surface->getVertices();
        }
        
        void MoveSurfaceCommand::undo(){
            //for (auto i = 0; i < _previousVertices.size(); i++) {
                //_surface->setVertex(i, _previousVertices[i]);
            //}
            _surface->moveBy(_previousVertices[0] - _surface->getVertices()[0]);
            _projectionEditor->updateJoints();
            _previousVertices.clear();
            _surface = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

