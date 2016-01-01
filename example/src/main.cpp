#include "ofMain.h"
#include "ofApp.h"
#include <string>

#ifdef TARGET_RASPBERRY_PI

	int main(int argc, char * argv[]){

		bool fullscreen = false;

		if(argc > 0){
			string fullscreenFlag = "-f";
			for(int i = 0; i < argc; i++){
				if(strcmp(argv[i], fullscreenFlag.c_str()) == 0){
					fullscreen = true;
					break;
				}
			}
		}

		if(fullscreen){
			ofSetupOpenGL(600, 500, OF_FULLSCREEN);
		}else{
			ofSetupOpenGL(800, 450, OF_WINDOW);
		}

		ofRunApp(new ofApp());
	}

#else

	int main(){
		ofSetupOpenGL(800, 600, OF_WINDOW);
		ofRunApp(new ofApp());
	}

#endif
