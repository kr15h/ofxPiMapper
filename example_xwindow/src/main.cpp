#include "ofMain.h"
#include "ofApp.h"
#include <string>
#include <vector>
#include "Settings.h"

int main(int argc, char * argv[]){
	bool fullscreen = false;

	std::vector<std::string> arguments = std::vector<std::string>(argv, argv + argc);
	for(size_t i = 0; i < arguments.size(); ++i){
		if(arguments.at(i) == "-f"){
			fullscreen = true;
			break;
		}
	}
	
	Settings::instance()->setFullscreen(fullscreen);

	ofSetupOpenGL(1600, 500, OF_WINDOW);
	ofRunApp(new ofApp());
}
