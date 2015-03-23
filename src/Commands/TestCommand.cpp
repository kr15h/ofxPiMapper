# include "TestCommand.h"

TestCommand::TestCommand(ofxPiMapper * a){
	_application = a;
}

void TestCommand::execute(){
	string name = "Hugo";
	_application->testCommand(name);
}