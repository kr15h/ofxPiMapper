#pragma once

/*
Joystick num axes: 5
Joystick ID: 0
Joystick Name: Generic   USB  Joystick  
Joystick GUID: 79000000000000000600000000000000
Joystick num axes: 2
Joystick ID: 1
Joystick Name: USB gamepad           
Joystick GUID: 1f0800000000000001e4000000000000
Joystick num axes: 6
Joystick ID: 2
Joystick Name: Wireless Controller
Joystick GUID: 4c05000000000000c405000000000000
Initialised 3 joysticks

// These are the strings reported by SDL2's SDL_JoystickGetGUIDString:
// https://wiki.libsdl.org/SDL_JoystickGetGUIDString
4c05c405000000000000504944564944 // Windows. Note characters 1-8.
4c05000000000000c405000000000000 // OSX.     Note characters 1-4 and 17-20.
030000004c050000c405000011010000 // Linux.   Note characters 9-12 and 17-20.

4c05c405 // This is the GUID string returned by FNA. Get it?


*/

#include <vector>
#include <iostream>
#include "SDL2/SDL.h"

class InputHandler{
	public:
		static InputHandler * instance();
		void initialise();
		void update();
		void clean();
		bool initialised();
	
	private:
		InputHandler(){}
		~InputHandler(){}
		static InputHandler * _instance;
		bool _initialised;
		std::vector<SDL_Joystick *> _joysticks;
};
