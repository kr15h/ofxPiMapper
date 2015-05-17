// SetGuiModeCmd
// Provides undo operation for setting the GUI mode/state
// Created by Krisjanis Rijnieks 2015-05-14

#pragma once

#include "SurfaceManagerGui.h"
#include "BaseCmd.h"

namespace ofx{
    namespace piMapper{
        
        class SetGuiModeCmd : public BaseUndoCmd{
        
            public:
                SetGuiModeCmd(SurfaceManagerGui * gui, int mode);
                void exec();
                void undo();
    
            private:
                SurfaceManagerGui * _gui;
                int _prevGuiMode;
                int _mode;
        };
        
    } // namespace piMapper
} // namespace ofx

