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

#ifdef TARGET_RASPBERRY_PI
	ofGLESWindowSettings settings;
	settings.setGLESVersion(2);
#else
	ofGLFWWindowSettings settings;
#endif

	//ofCreateWindow(settings);
	ofSetupOpenGL(800, 450, OF_WINDOW);
	ofRunApp(new ofApp());
}
