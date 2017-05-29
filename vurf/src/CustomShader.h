#pragma once

#include "ofMain.h"
#include "FboSource.h"

class CustomShader : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();

		int framecount;

		ofShader shader;
};


