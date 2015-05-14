// MoveSurfaceVertexCommand
// Provides with option to undo move surface vertex operation.
// Created by Krisjanis Rijnieks 2015-05-15

#pragma once

#include "BaseCommand.h"
#include "BaseSurface.h"
#include "ProjectionEditor.h"
#include "BaseJoint.h"

namespace ofx{
    namespace piMapper{
        
        class MoveSurfaceVertexCommand : public BaseUndoableCommand{
        
            public:
                MoveSurfaceVertexCommand(
                    int vertIndex,
                    BaseSurface * surface,
                    ProjectionEditor * projectionEditor);
                void exec();
                void undo();
    
            private:
                int _vertIndex;
                ofVec2f _prevVertPos;
                BaseSurface * _surface;
                ProjectionEditor * _projectionEditor;
        };
        
    } // namespace piMapper
} // namespace ofx

