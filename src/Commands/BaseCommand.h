// Command base class for separating ofxPiMapper available commands from the core.
// Created by Krisjanis Rijnieks 2015-03-23

// Good example
// http://gameprogrammingpatterns.com/command.html
// This file contains declarations of both:
//  - non-undoable command base class
//  - undoable command base class

#pragma once

namespace ofx{
    namespace piMapper{

        // Base class for all commands
        class BaseCommand{
            public:
                virtual ~BaseCommand(){};
                virtual void exec() = 0;
            
                // By default a command is not undo
                virtual bool isUndoable(){return false;}
                
            protected:
                // In order to avoid using this class directly,
                // we make the constructor protected.
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
