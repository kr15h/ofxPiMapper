#include "ofMain.h"
#include "ofApp.h"
#include <string>
#include <vector>
#include "Settings.h"

int main(int argc, char * argv[]){
	bool fullscreen = false;

	vector<string> arguments = vector<string>(argv, argv + argc);
	for(int i = 0; i < arguments.size(); ++i){
		if(arguments.at(i) == "-f"){
			fullscreen = true;
			break;
		}
	}

	Settings::instance()->setFullscreen(fullscreen);
	//ofSetupOpenGL(1024, 768, OF_WINDOW);
	//ofSetupOpenGL(800, 450, OF_WINDOW);
	
	int w = 1024;
	int h = 768;
	ofWindowMode mode = OF_WINDOW;

	// Loglever festlegen
    ofSetLogLevel(OF_LOG_VERBOSE);

    ofGLESWindowSettings settings;
    settings.width = w;
    settings.height = h;
    settings.setGLESVersion(2);
    settings.windowMode = mode;
    ofCreateWindow(settings);


	ofRunApp(new ofApp());
}
