#include "ofApp.h"
#include <string>
#include <vector>

int main(int argc, char * argv[]){
	bool fullscreen = false;

	std::vector<std::string> arguments = std::vector<std::string>(argv, argv + argc);
	for(size_t i = 0; i < arguments.size(); ++i){
		if(arguments.at(i) == "-f"){
			fullscreen = true;
			break;
		}
	}

	if(fullscreen){
		ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
	}else{
		ofSetupOpenGL(800, 450, OF_WINDOW);
	}

	
	ofRunApp(new ofApp());
}
