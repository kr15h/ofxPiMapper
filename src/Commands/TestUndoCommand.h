// Created by Krisjanis Rijnieks 2015-03-25

#pragma once

#include "ofxPiMapper.h"
#include "BaseCommand.h"

class ofxPiMapper;

namespace ofx{
    namespace piMapper{
        
        class TestUndoCommand : public BaseUndoableCommand{
        
            public:
                TestUndoCommand(ofxPiMapper * a);
                void exec();
                void undo();
    
            private:
                ofxPiMapper * _application;
                int increase;
        };
        
    } // namespace piMapper
} // namespace ofx

