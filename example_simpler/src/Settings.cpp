#include "Settings.h"

Settings * Settings::_instance = 0;

Settings * Settings::instance(){
	if(_instance == 0){
		_instance = new Settings();
	}
	return _instance;
}

Settings::Settings(){
	_fullscreen = false;
}

void Settings::setFullscreen(bool f){
	_fullscreen = f;
}

bool Settings::getFullscreen(){
	return _fullscreen;
}