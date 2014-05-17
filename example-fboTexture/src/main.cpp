#include "ofMain.h"
#include "ofApp.h"

int main()
{
#ifdef TARGET_RASPBERRY_PI
	ofSetupOpenGL(600, 500, OF_FULLSCREEN);
#else
    ofSetupOpenGL(600, 500, OF_WINDOW);
#endif
	ofRunApp(new ofApp());
}