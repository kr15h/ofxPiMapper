#include "TerminalListener.h"

KeyListenerEventData::KeyListenerEventData(char character, void * listener){
	this->character = character;
	this->listener = listener;
}

TerminalListener::TerminalListener(){
	sleepTime = 100;
	listener = 0;
}

TerminalListener::~TerminalListener(){
	close();
}

void TerminalListener::setup(KeyListener * listener_, int sleepTime_ = 0){
	listener = listener_;

	if(sleepTime_ > 0){
		sleepTime = sleepTime_;
	}

	struct termios new_termios;

	tcgetattr(STDIN_FILENO, &orig_termios);

	new_termios = orig_termios;
	new_termios.c_lflag &= ~(ICANON | ECHO | ECHOCTL | ECHONL);
	new_termios.c_cflag |= HUPCL;
	new_termios.c_cc[VMIN] = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	thread.start(*this);
}

void TerminalListener::run(){
	while (thread.isRunning()){
		if (listener != NULL){
			int ch[8];
			int chnum = 0;

			while ((ch[chnum] = getchar()) != EOF){
				chnum++;
			}

			if (chnum > 1){
				ch[0] = ch[chnum - 1];
			}else{
				(ch[chnum - 2] << 8);
			}

			if (chnum > 0){
				//ofLog(OF_LOG_VERBOSE, "TerminalListener: character %c", ch[0]);
				KeyListenerEventData eventData(ch[0], (void *)this);
				listener->onCharacterReceived(eventData);
			}

			thread.sleep(sleepTime);
		}
	}
}

void TerminalListener::close(){
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
	thread.tryJoin(50);
	listener = NULL;
}
