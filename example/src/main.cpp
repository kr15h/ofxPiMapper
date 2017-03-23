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

	int w = 800;
	int h = 450;
	ofWindowMode mode = OF_WINDOW;

#ifdef TARGET_RASPBERRY_PI
	ofGLESWindowSettings settings;
	settings.setGLESVersion(2);
	settings.width = w;
	settings.height = h;
	settings.windowMode = mode;
	ofCreateWindow(settings);
#else
	ofSetupOpenGL(w, h, mode);
#endif

	ofRunApp(new ofApp());
}
