#pragma once

#include "BaseCmd.h"
#include "Application.h"

namespace ofx {
    namespace piMapper {
    
        class Application;
        class ApplicationBaseState;
        
        class SetApplicationStateCmd : public BaseUndoCmd {
        
            public:
                SetApplicationStateCmd(
                    Application * app,
                    ApplicationBaseState * st,
                    SurfaceManagerGui * gui,
                    int mode);

                void exec();
                void undo();
    
            private:
                Application * _application;
                ApplicationBaseState * _prevApplicationState;
                ApplicationBaseState * _applicationState;
            
                // TODO: Remove these after porting to app state system is done
                SurfaceManagerGui * _gui;
                int _prevGuiMode;
                int _mode;
        };
        
    } // namespace piMapper
} // namespace ofx

