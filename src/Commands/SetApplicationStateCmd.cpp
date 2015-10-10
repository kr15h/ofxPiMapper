#include "SetApplicationStateCmd.h"

namespace ofx {
    namespace piMapper {
        
        SetApplicationStateCmd::SetApplicationStateCmd(
            Application * app,
            ApplicationBaseState * st) {
            
            _application = app;
            _prevApplicationState = 0;
            _applicationState = st;
        }

        void SetApplicationStateCmd::exec() {
            _prevApplicationState = _application->getState();
            _application->setState(_applicationState);
        }
        
        void SetApplicationStateCmd::undo() {
            ofLogNotice("SetApplicationStateCmd", "undo");
            _application->setState(_prevApplicationState);
        }
        
    } // namespace piMapper
} // namespace ofx

