// RemoveSurfaceCommand
// Provides with option to undo remove surface operation.
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "ofxPiMapper.h"
#include "BaseCommand.h"
#include "BaseSurface.h"

class ofxPiMapper;

namespace ofx{
    namespace piMapper{
        
        class RemoveSurfaceCommand : public BaseUndoableCommand{
        
            public:
                RemoveSurfaceCommand(ofxPiMapper * app);
                void exec();
                void undo();
    
            private:
                ofxPiMapper * _app;
                BaseSurface * _surface;
        };
        
    } // namespace piMapper
} // namespace ofx

