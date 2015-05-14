#pragma once

#import <deque>
#import "BaseCommand.h"

namespace ofx{
    namespace piMapper{

        class CommandManager{
            
            public:
                void executeCommand(BaseCommand * cmd);
                void undo();
                // TODO: Add redo
            
            private:
                std::deque<BaseUndoableCommand *> commandStack;
                // TODO: Add redo stack
                //       Maybe use vector instead of deque...
        };
        
    } // namespace piMapper
} // namespace ofx