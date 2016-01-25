#include "ofMain.h"
#include "ofApp.h"
#include <string>
#include <vector>

int main(int argc, char * argv[]){
	bool fullscreen = false;

	vector<string> arguments = vector<string>(argv, argv + argc);
	for(int i = 0; i < arguments.size(); ++i){
		if(arguments.at(i) == "-f"){
			fullscreen = true;
			break;
		}
	}

	if(fullscreen){
		ofSetupOpenGL(800, 450, OF_FULLSCREEN);
	}else{
		ofSetupOpenGL(800, 450, OF_WINDOW);
	}

	ofRunApp(new ofApp());
}
