#include "SetGuiModeCmd.h"

namespace ofx{
    namespace piMapper{
        
        SetGuiModeCmd::SetGuiModeCmd(SurfaceManagerGui * gui, int mode){
            _gui = gui;
            _prevGuiMode = -1;
            _mode = mode;
        }

        void SetGuiModeCmd::exec(){
            _prevGuiMode = _gui->getMode();
            _gui->setMode(_mode);
        }
        
        void SetGuiModeCmd::undo(){
            ofLogNotice("SetGuiModeCmd", "undo");
            _gui->setMode(_prevGuiMode);
        }
        
    } // namespace piMapper
} // namespace ofx

