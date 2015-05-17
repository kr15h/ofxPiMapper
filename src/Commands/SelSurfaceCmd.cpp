#include "SelSurfaceCmd.h"

namespace ofx{
    namespace piMapper{
        
        SelSurfaceCmd::SelSurfaceCmd(
            SurfaceManager * surfaceManager,
            BaseSurface * surfaceToSelect,
            ProjectionEditor * projectionEditor){
            
            _surfaceManager = surfaceManager;
            _surfaceToSelect = surfaceToSelect;
            _projectionEditor = projectionEditor;
        }

        void SelSurfaceCmd::exec(){
            _prevSelectedSurface = _surfaceManager->getSelectedSurface();
            _projectionEditor->clearJoints();
            _surfaceManager->selectSurface(_surfaceToSelect);
            _projectionEditor->createJoints();
        }
        
        void SelSurfaceCmd::undo(){
            ofLogNotice("SelSurfaceCmd", "undo");
            _projectionEditor->clearJoints();
            _surfaceManager->selectSurface(_prevSelectedSurface);
            _projectionEditor->createJoints();
            _surfaceToSelect = 0;
            _prevSelectedSurface = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

