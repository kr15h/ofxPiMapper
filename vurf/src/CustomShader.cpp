#include "CustomShader.h"

void CustomShader::setup(){
	// Give our source a decent name
	name = "Custom Shader Source";

	// Allocate our FBO source, decide how big it should be
	allocate(500, 500);

	framecount = 0;


#ifdef TARGET_OPENGLES
	shader.load("shadersES2/shader");
	ofLog(OF_LOG_NOTICE, "***ES2");
#else
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader");
	ofLog(OF_LOG_NOTICE, "***GL3");
	}else{
		shader.load("shadersGL2/shader");
	ofLog(OF_LOG_NOTICE, "***Gl2");
	}
#endif


}

// Don't do any drawing here
void CustomShader::update(){

	framecount ++;
}


// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void CustomShader::draw(){
	ofClear(0);
	shader.begin();
	shader.setUniform1f("time",ofGetElapsedTimef());
    
    	//ofDrawRectangle(0, 0, 500, 500);
    	ofDrawRectangle(0, 0, 500, 500);
    	shader.end();

}
