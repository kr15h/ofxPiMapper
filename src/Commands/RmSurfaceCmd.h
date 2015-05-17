// RmSurfaceCmd
// Provides with option to undo remove surface operation.
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "ofxPiMapper.h"
#include "BaseCmd.h"
#include "BaseSurface.h"

class ofxPiMapper;

namespace ofx{
    namespace piMapper{
        
        class RmSurfaceCmd : public BaseUndoCmd{
        
            public:
                RmSurfaceCmd(ofxPiMapper * app);
                void exec();
                void undo();
    
            private:
                ofxPiMapper * _app;
                BaseSurface * _surface;
        };
        
    } // namespace piMapper
} // namespace ofx

