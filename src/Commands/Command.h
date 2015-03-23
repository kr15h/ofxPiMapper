// Command base class for separating ofxPiMapper available commands from the core.
// Created by Krisjanis Rijnieks 2015-03-23

#pragma once

class Command{
	public:
		virtual void execute() = 0;
};