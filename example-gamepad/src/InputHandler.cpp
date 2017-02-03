#include "InputHandler.h"

InputHandler * InputHandler::_instance = 0;

InputHandler * InputHandler::instance(){
	if(_instance == 0){
		_instance = new InputHandler();
	}
	return _instance;
}

void InputHandler::initialise(){
	/*
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	*/
	
	if(SDL_Init(SDL_INIT_JOYSTICK) >= 0){
		std::cout << "Joystick INIT success" << std::endl;
	}
	
	if(SDL_NumJoysticks() > 0){
		for(int i = 0; i < SDL_NumJoysticks(); ++i){
			SDL_Joystick * joystick = SDL_JoystickOpen(i);
			if(SDL_JoystickGetAttached(joystick) == SDL_TRUE){
				std::cout << "Joystick num axes: " << SDL_JoystickNumAxes(joystick) << std::endl;
				std::cout << "Joystick ID: " << SDL_JoystickInstanceID(joystick) << std::endl;
				std::cout << "Joystick Name: " << SDL_JoystickName(joystick) << std::endl;
				
				SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(i);
				char guid_str[1024];
				SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
				std::cout << "Joystick GUID: " << guid_str << std::endl;
				
				_joysticks.push_back(joystick);
			}else{
				std::cout << SDL_GetError() << std::endl;
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		_initialised = true;
		std::cout << "Initialised " << _joysticks.size() << " joysticks" << std::endl;
	}else{
		_initialised = false;
		std::cout << "No joysticks initialised" << std::endl;
	}
}

void InputHandler::update(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		
		if(event.type == SDL_QUIT){
			std::cout << "SDL_QUIT on InputHandler::update()" << std::endl;
		}
		
		if(event.type == SDL_JOYBALLMOTION){
			std::cout << "SDL_JOYBALLMOTION" << std::endl;
		}
		
		if(event.type == SDL_JOYHATMOTION){
			std::cout << "SDL_JOYHATMOTION" << std::endl;
			if(event.jhat.value == SDL_HAT_CENTERED){
				std::cout << "value: centered" << std::endl;
			}else if(event.jhat.value == SDL_HAT_LEFT){
				std::cout << "value: left" << std::endl;
			}else if(event.jhat.value == SDL_HAT_RIGHT){
				std::cout << "value: right" << std::endl;
			}else if(event.jhat.value == SDL_HAT_UP){
				std::cout << "value: up" << std::endl;
			}else if(event.jhat.value == SDL_HAT_DOWN){
				std::cout << "value: down" << std::endl;
			}else if(event.jhat.value == SDL_HAT_RIGHTUP){
				std::cout << "value: rightup" << std::endl;
			}else if(event.jhat.value == SDL_HAT_RIGHTDOWN){
				std::cout << "value: rightdown" << std::endl;
			}else if(event.jhat.value == SDL_HAT_LEFTUP){
				std::cout << "value: leftup" << std::endl;
			}else if(event.jhat.value == SDL_HAT_LEFTDOWN){
				std::cout << "value: leftdown" << std::endl;
			}
			std::cout << "----------" << std::endl;
		}
		
		if(event.type == SDL_JOYAXISMOTION){
			if((event.jaxis.value < -3200) || (event.jaxis.value > 3200)){
				std::cout << "SDL_JOYAXISMOTION" << std::endl;
				std::cout << "type: " << event.jaxis.type << std::endl;
				std::cout << "which: " << event.jaxis.which << std::endl;
				std::cout << "axis: " << event.jaxis.axis << std::endl;
				std::cout << "value: " << event.jaxis.value << std::endl;
				
				if(event.jaxis.axis == 0){
					std::cout << "axis check: left-right" << std::endl;
				}

				if(event.jaxis.axis == 1){
					std::cout << "axis check: up-down" << std::endl;
				}
				
				if(event.jaxis.axis == 2){
					std::cout << "axis check: 2" << std::endl;
				}
				
				if(event.jaxis.axis == 3){
					std::cout << "axis check: 3" << std::endl;
				}
				
				// Sony PlayStation Wireless controller
				if(event.jaxis.axis == 4){
					std::cout << "axis check: 4" << std::endl;
				}
				
				if(event.jaxis.axis == 5){
					std::cout << "axis check: 5" << std::endl;
				}
				
				std::cout << "----------" << std::endl;
			}
		}
		
		if(event.type == SDL_JOYBUTTONDOWN){
			std::cout << "SDL_JOYBUTTONDOWN" << std::endl;
			std::cout << "type: " << event.jbutton.type << std::endl;
			std::cout << "which: " << event.jbutton.which << std::endl;
			
			std::cout << "button: " << (int)event.jbutton.button << std::endl;
			/*
			std::cout << "button: ";
			if(event.jbutton.button == SDL_BUTTON_X1){
				std::cout << "SDL_BUTTON_X1";
			}
			std::cout << std::endl;
			*/
			
			std::cout << "state: " << event.jbutton.state << std::endl;
			std::cout << "----------" << std::endl;
		}
	}
}

void InputHandler::clean(){
	if(_initialised){
		for(int i = 0; i < _joysticks.size(); ++i){
			SDL_JoystickClose(_joysticks[i]);
		}
	}
	
}

bool InputHandler::initialised(){
	return _initialised;
}
