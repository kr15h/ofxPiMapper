// Command base class for separating ofxPiMapper available commands from the core.
// Created by Krisjanis Rijnieks 2015-03-23

// Good example
// http://gameprogrammingpatterns.com/command.html

#pragma once

namespace ofx{
    namespace piMapper{

        // Base class for all commands
        class BaseCommand{
        
            public:
                virtual ~BaseCommand(){};
                virtual void execute() = 0;
                virtual bool isUndoable(){return false;}
                
            protected:
                BaseCommand(){};
        };

        // Base class for all undoable commands
        class BaseUndoableCommand : public BaseCommand{
            
            public:
                virtual void undo() = 0;
                virtual bool isUndoable(){return true;}
                
            protected:
                BaseUndoableCommand(){};
        };
    
    } // namespace piMapper
} // namespace ofx

// Ideas for command classes
// SelectSurfaceCommand
// MoveSurfaceCommand
// SelectSourceMapCommand
// MoveSourceMapCommand
