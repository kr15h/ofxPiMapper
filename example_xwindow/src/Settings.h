#pragma once

#include "ofMain.h"

class Settings {
	public:
		static Settings * instance();
	
		void setFullscreen(bool f);
		bool getFullscreen();
	
	private:
		static Settings * _instance;
	
		Settings();

		bool _fullscreen;
};
