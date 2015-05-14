#include "MoveSurfaceVertexCommand.h"

namespace ofx{
    namespace piMapper{
        
        MoveSurfaceVertexCommand::MoveSurfaceVertexCommand(
            int vertIndex,
            BaseSurface * surface,
            ProjectionEditor * projectionEditor){
            
            _vertIndex = vertIndex;
            _surface = surface;
            _projectionEditor = projectionEditor;
        }

        void MoveSurfaceVertexCommand::exec(){
            ofLogNotice("MoveJointCommand", "exec");
            _prevVertPos = _surface->getVertices()[_vertIndex];
        }
        
        void MoveSurfaceVertexCommand::undo(){
            ofLogNotice("MoveJointCommand", "undo");
            _surface->setVertex(_vertIndex, _prevVertPos);
            _projectionEditor->updateJoints();
            _projectionEditor = 0;
            _surface = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

