// CommandManager class to keep a stack of commands for undo functionality
// Created by Krisjanis Rijnieks 2015-03-24

#pragma once

#import <deque>
#import "BaseCommand.h"

namespace ofx{
    namespace piMapper{

        class CommandManager{
            
            public:
                void executeCommand(BaseCommand * cmd);
                void undo();
            
            private:
                std::deque<BaseUndoableCommand *> commandStack;
        };
        
    } // namespace piMapper
} // namespace ofx