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
                    ApplicationBaseState * st);

                void exec();
                void undo();
    
            private:
                Application * _application;
                ApplicationBaseState * _prevApplicationState;
                ApplicationBaseState * _applicationState;
        };
        
    } // namespace piMapper
} // namespace ofx

