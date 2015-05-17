#include "MvSurfaceCmd.h"

namespace ofx{
    namespace piMapper{
        
        MvSurfaceCmd::MvSurfaceCmd(
            BaseSurface * surface,
            ProjectionEditor * projectionEditor){
            
            _surface = surface;
            _projectionEditor = projectionEditor;
        }

        void MvSurfaceCmd::exec(){
            ofLogNotice("MvSurfaceCmd", "exec");
            _previousVertices = _surface->getVertices();
            _surface->setMoved(false);
        }
        
        void MvSurfaceCmd::undo(){
            ofLogNotice("MvSurfaceCmd", "undo");
            _surface->moveBy(_previousVertices[0] - _surface->getVertices()[0]);
            _projectionEditor->updateJoints();
            _previousVertices.clear();
            _surface = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

