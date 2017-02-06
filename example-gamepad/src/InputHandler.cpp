#include "InputHandler.h"

InputHandler * InputHandler::_instance = 0;

InputHandler * InputHandler::instance(){
	if(_instance == 0){
		_instance = new InputHandler();
	}
	return _instance;
}

void InputHandler::initialise(){

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
		return;
	}
	
	// Load the controllers.xml file if exists.
	if(ofFile::doesFileExist("controllers.xml")){
		ofxXmlSettings xml;
		if(!xml.load("controllers.xml")){
			std::cout << "Failed to load controllers.xml" << std::endl;
		}
		
		std::cout << "Loaded controllers.xml" << std::endl;
		
		// Find the right map for each initialized controller
		for(int i = 0; i < _joysticks.size(); ++i){
			
			// Get controller GUID first
			SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(i);
			char guid_str[1024];
			SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
			std::string guidString(guid_str);
			
			// Search for GUID in XML
			if(xml.tagExists("controllers")){
				xml.pushTag("controllers");
				
				for(int ci = 0; ci < xml.getNumTags("controller"); ci++){
					if(xml.tagExists("controller", ci)){
						xml.pushTag("controller", ci);
						
						if(xml.getValue("guid_osx", "") == guidString ||
						 xml.getValue("guid_linux", "") == guidString ||
						 xml.getValue("guid_windows", "") == guidString){
							
							std::cout << "Found map for GUID: " << guidString << std::endl;
							
							// We found our controller for the initialized joystick, let's map it
							std::map<ControllerCommand, ControllerItem> map;
							map[COMMAND_LEFT] = getControllerItem(xml.getValue("left", ""));
							map[COMMAND_RIGHT] = getControllerItem(xml.getValue("right", ""));
							map[COMMAND_UP] = getControllerItem(xml.getValue("up", ""));
							map[COMMAND_DOWN] = getControllerItem(xml.getValue("down", ""));
							map[COMMAND_A] = getControllerItem(xml.getValue("a", ""));
							map[COMMAND_B] = getControllerItem(xml.getValue("b", ""));
							map[COMMAND_X] = getControllerItem(xml.getValue("x", ""));
							map[COMMAND_Y] = getControllerItem(xml.getValue("y", ""));
							map[COMMAND_SELECT] = getControllerItem(xml.getValue("select", ""));
							map[COMMAND_START] = getControllerItem(xml.getValue("start", ""));
							
							// Add map to our database for a controller only if it is found
							_controllerMap[i] = map;
							
							// Return the xml oblect to the state before the for loop
							xml.popTag(); // controller[ci]
							
							// Break the for loop as we found what we wanted
							break;
						}
						
						// Return the xml oblect to the state before the for loop
						xml.popTag(); // controller[ci]
					}
				}
				xml.popTag(); // controllers
			} // if(xml.tagExists("controllers"))
		} // ofFile::doesFileExist("controllers.xml")
	}else{
		std::cout << "controllers.xml does not exist" << std::endl;
	}
}

void InputHandler::update(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
	
		ControllerCommand command = ControllerCommand::COMMAND_NONE;
		
		if(event.type == SDL_JOYHATMOTION){
			std::cout << "SDL_JOYHATMOTION" << std::endl;
		
			ControllerItem item;
			item.type = CONTROLLER_HAT;
			item.index = (int)event.jhat.hat;
			item.value = (int)event.jhat.value;
			
			command = getControllerCommand((int)event.jhat.which, item);
			std::cout << "hat value: " << item.value << std::endl;
			std::cout << "command: " << controllerCommandToString(command) << std::endl;
			std::cout << "----------" << std::endl;
		}
		
		if(event.type == SDL_JOYAXISMOTION){
			if((event.jaxis.value < -3200) || (event.jaxis.value > 3200)){
				std::cout << "SDL_JOYAXISMOTION" << std::endl;
				
				ControllerItem item;
				item.type = CONTROLLER_AXIS;
				item.index = (int)event.jaxis.axis;
				item.value = (int)event.jaxis.value;
			
				command = getControllerCommand((int)event.jaxis.which, item);
				std::cout << "command: " << controllerCommandToString(command) << std::endl;
				std::cout << "----------" << std::endl;
		
			}
		}
		
		if(event.type == SDL_JOYBUTTONDOWN){
			std::cout << "SDL_JOYBUTTONDOWN" << std::endl;
			
			ControllerItem item;
			item.type = CONTROLLER_BUTTON;
			item.index = (int)event.jbutton.button;
			item.value = 1; // Button has only one value
			
			command = getControllerCommand((int)event.jbutton.which, item);
			std::cout << "command: " << controllerCommandToString(command) << std::endl;
			std::cout << "----------" << std::endl;
		}
		
		if(command != ControllerCommand::COMMAND_NONE){
			ofSendMessage(ofMessage(ofToString(command)));
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

ControllerItem InputHandler::getControllerItem(std::string code){
	ControllerItem item;
	
	// Determine type
	if(code.substr(0, 1) == "b"){
		item.type = CONTROLLER_BUTTON;
	}else if(code.substr(0, 1) == "h"){
		item.type = CONTROLLER_HAT;
	}else if(code.substr(0, 1) == "a"){
		item.type = CONTROLLER_AXIS;
	}
	
	// If it is a hat, we need a value, otherwise set it to -1
	if(item.type == CONTROLLER_HAT){
		item.index = ofToInt(code.substr(1, 1));
		item.value = ofToInt(code.substr(3));
	}else{
		item.index = ofToInt(code.substr(1));
		item.value = -1;
	}
	
	return item;
}

ControllerCommand InputHandler::getControllerCommand(int controllerIndex, ControllerItem & item){
	std::cout << "controllerIndex: " << controllerIndex << std::endl;
	
	std::map<int, std::map<ControllerCommand, ControllerItem>>::iterator it;
	it = _controllerMap.find(controllerIndex);
	if(it == _controllerMap.end()){
		return ControllerCommand::COMMAND_NONE;
	}
	
	std::map<ControllerCommand, ControllerItem>::iterator mit;
	for(mit = it->second.begin(); mit != it->second.end(); mit++){
		if(mit->second.type == item.type && mit->second.index == item.index){
			
			// In case of axes, we need to check the sign
			if(mit->second.type == CONTROLLER_AXIS){
				if(mit->first == ControllerCommand::COMMAND_LEFT && item.value > 0){
					continue; // value must be negative for left
				}
				
				if(mit->first == ControllerCommand::COMMAND_RIGHT && item.value < 0){
					continue; // value must be positive for right
				}
				
				if(mit->first == ControllerCommand::COMMAND_UP && item.value > 0){
					continue; // value must be negative for up
				}
				
				if(mit->first == ControllerCommand::COMMAND_DOWN && item.value < 0){
					continue; // value must be positive for down
				}
				
				return mit->first;
			}
			
			// In case of hat, we need to compare hat values
			if(mit->second.type == CONTROLLER_HAT){
				if(mit->second.value == item.value){
					return mit->first;
				}else{
					continue;
				}
			}
			
			// In case of buttons type and index is enough
			return mit->first;
		}
	}
	
	return ControllerCommand::COMMAND_NONE;
}

std::string InputHandler::controllerCommandToString(ControllerCommand com){
	if(com == COMMAND_NONE){
		return "COMMAND_NONE";
	}else if(com == COMMAND_LEFT){
		return "COMMAND_LEFT";
	}else if(com == COMMAND_RIGHT){
		return "COMMAND_RIGHT";
	}else if(com == COMMAND_UP){
		return "COMMAND_UP";
	}else if(com == COMMAND_DOWN){
		return "COMMAND_DOWN";
	}else if(com == COMMAND_A){
		return "COMMAND_A";
	}else if(com == COMMAND_B){
		return "COMMAND_B";
	}else if(com == COMMAND_X){
		return "COMMAND_X";
	}else if(com == COMMAND_Y){
		return "COMMAND_Y";
	}else if(com == COMMAND_SELECT){
		return "COMMAND_SELECT";
	}else if(com == COMMAND_START){
		return "COMMAND_START";
	}else{
		
	}
}

