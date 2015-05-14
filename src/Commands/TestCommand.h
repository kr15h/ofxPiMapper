// TestCommand class, extends Command base class. Used for Command design pattern implementation
// pre-tests. Will be removed as soon as possible.
// Created by Krisjanis Rijnieks 2015-03-23

#pragma once

#include "ofxPiMapper.h"
#include "BaseCommand.h"

class ofxPiMapper;

namespace ofx{
    namespace piMapper{
        
        class TestCommand : public BaseCommand{
        
            public:
                TestCommand(ofxPiMapper * a);
                void exec();
    
            private:
                ofxPiMapper * _application;
        };
        
    } // namespace piMapper
} // namespace ofx

