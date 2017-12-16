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

	shared_ptr<ofAppBaseWindow> window;
#ifdef TARGET_OPENGLES
	ofGLESWindowSettings esSettings;
	esSettings.glesVersion = 2;
	esSettings.width = 1440;
	esSettings.height = 900;
	window = ofCreateWindow(esSettings);
#else
	ofGLWindowSettings glSettings;
	glSettings.glVersionMajor = 2;
	glSettings.glVersionMinor = 1;
	glSettings.width = 1440;
	glSettings.height = 900;
	window = ofCreateWindow(glSettings);
#endif

	auto app = std::make_shared<ofApp>();
	Settings::instance()->setFullscreen(fullscreen);
	ofRunApp(window, app);
	ofRunMainLoop();
}
