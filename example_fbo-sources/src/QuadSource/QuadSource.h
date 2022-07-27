#pragma once

#include "ofMain.h"
#include "FboSource.h"

class QuadSource : public ofx::piMapper::FboSource {
	public:
    void setup();
		void update();
		void draw();

		std::vector<ofRectangle> quads;
		std::vector<float> quadSpeeds;
};
