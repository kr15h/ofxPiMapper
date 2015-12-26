// Command base class for separating ofxPiMapper available commands from the core.
// Created by Krisjanis Rijnieks 2015-03-23

// Good example
// http://gameprogrammingpatterns.com/command.html
// This file contains declarations of both:
//  - non-undoable command base class
//  - undoable command base class

#pragma once

namespace ofx {
namespace piMapper {

// Base class for all commands
class BaseCmd {

	public:
		virtual ~BaseCmd(){}
		virtual void exec() = 0;

		// By default a command is not undo
		virtual bool isUndoable(){
			return false;
		}

	protected:
		// In order to avoid using this class directly,
		// we make the constructor protected.
		BaseCmd(){}

};

// Base class for all undoable commands
class BaseUndoCmd : public BaseCmd {

	public:
		virtual void undo() = 0;
		virtual bool isUndoable(){
			return true;
		}

	protected:
		BaseUndoCmd(){}

};

} // namespace piMapper
} // namespace ofx
