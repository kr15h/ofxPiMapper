# include "TestCommand.h"

namespace ofx{
    namespace piMapper{
        
        TestCommand::TestCommand(ofxPiMapper * a){
            _application = a;
        }

        void TestCommand::exec(){
            string name = "Hugo";
            _application->testCommand(name);
        }
        
    } // namespace piMapper
} // namespace ofx

