/* 
 * TerminalListener
 * Helper for capturing keyboard input when via SSH
 * Author: Jason Van Cleave / https://github.com/jvcleave
 * Adaptor: Krisjanis Rijnieks / https://github.com/kr15h
 */

#pragma once

#include "ofMain.h"
#include <fcntl.h>

namespace ofx {
namespace piMapper {

class KeyListenerEventData {
	public:
		KeyListenerEventData(char character, void * listener);
		void * listener;
		char character;
};

class KeyListener {
	public:
		virtual void onCharacterReceived(KeyListenerEventData & e) = 0;
};


class TerminalListener : public Poco::Runnable {
	private:
		struct termios orig_termios;
	
	public:
		TerminalListener();
		~TerminalListener();
	
		void setup(KeyListener* listener_, int sleepTime_);
		void run();
		void close();
	
		KeyListener* listener;
		Poco::Thread thread;
		int sleepTime;
};

} // namespace piMapper
} // namespace ofx