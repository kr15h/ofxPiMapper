#pragma once

// These are the strings reported by SDL2's SDL_JoystickGetGUIDString:
// https://wiki.libsdl.org/SDL_JoystickGetGUIDString

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "SDL2/SDL.h"
#include "ofMain.h"
#include "ofxXmlSettings.h"

enum ControllerItemType{
	CONTROLLER_BUTTON,
	CONTROLLER_AXIS,
	CONTROLLER_HAT
};

enum ControllerCommand{
	COMMAND_NONE,
	COMMAND_LEFT,
	COMMAND_RIGHT,
	COMMAND_UP,
	COMMAND_DOWN,
	COMMAND_A,
	COMMAND_B,
	COMMAND_X,
	COMMAND_Y,
	COMMAND_SELECT,
	COMMAND_START
};

struct ControllerItem{
	ControllerItemType type;
	int index;
	int value;
};

class InputHandler{
	public:
		static InputHandler * instance();
	
		void initialise();
		void update();
		void clean();
	
		bool initialised();
	
		ControllerItem getControllerItem(std::string code);
		ControllerCommand getControllerCommand(int controllerIndex, ControllerItem & item);
		std::string controllerCommandToString(ControllerCommand com);
	
	private:
		InputHandler(){}
		~InputHandler(){}
		static InputHandler * _instance;
		bool _initialised;
		std::vector<SDL_Joystick *> _joysticks;
		std::map<int, std::map<ControllerCommand, ControllerItem>> _controllerMap;
};
