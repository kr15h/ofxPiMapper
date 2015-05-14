#pragma once

#import <vector>
#import "BaseCommand.h"
#import "ofLog.h"

namespace ofx{
    namespace piMapper{
        
        class CommandManager{
            public:
                void exec(BaseCommand * cmd);
                void undo();
                
            private:
                std::vector<BaseUndoableCommand *> commandStack;
        };
        
    } // namespace piMapper
} // namespace ofx