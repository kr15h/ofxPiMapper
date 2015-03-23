// TestCommand class, extends Command base class. Used for Command design pattern implementation
// pre-tests. Will be removed as soon as possible.
// Created by Krisjanis Rijnieks 2015-03-23

#pragma once

#include "ofxPiMapper.h"
#include "Command.h"

class ofxPiMapper;

class TestCommand : public Command{
	public:
		TestCommand(ofxPiMapper * a);
		~TestCommand();
		virtual void execute();
	
	private:
		ofxPiMapper * _application;
	
};