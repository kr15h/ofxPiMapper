// MvSurfaceCmd
// Provides with option to undo move surface operation.
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "ProjectionEditor.h"

namespace ofx{
    namespace piMapper{
        
        class MvSurfaceCmd : public BaseUndoCmd{
        
            public:
                MvSurfaceCmd(
                    BaseSurface * surface,
                    ProjectionEditor * projectionEditor);
                void exec();
                void undo();
    
            private:
                BaseSurface * _surface;
                ProjectionEditor * _projectionEditor;
                vector<ofVec3f> _previousVertices;
        };
        
    } // namespace piMapper
} // namespace ofx

