#pragma once

#import <vector>
#import "BaseCmd.h"
#import "ofLog.h"

namespace ofx{
    namespace piMapper{
        
        class CmdManager{
            public:
                void exec(BaseCmd * cmd);
                void undo();
                
            private:
                std::vector<BaseUndoCmd *> cmdStack;
        };
        
    } // namespace piMapper
} // namespace ofx