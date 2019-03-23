#include "ofMain.h"
#include "ofApp.h"

int main(){
	ofGLFWWindowSettings settings;
    settings.windowMode = OF_FULLSCREEN;
    ofCreateWindow(settings);
    ofRunApp(new ofApp);
}
