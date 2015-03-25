#include "TestUndoCommand.h"

namespace ofx{
    namespace piMapper{
        
        TestUndoCommand::TestUndoCommand(ofxPiMapper * a){
            _application = a;
        }

        void TestUndoCommand::execute(){
            increase = 2;
            _application->testUndoableCommand(increase);
        }
        
        void TestUndoCommand::undo(){
            _application->testUndoableCommand(-increase);
        }
        
    } // namespace piMapper
} // namespace ofx

