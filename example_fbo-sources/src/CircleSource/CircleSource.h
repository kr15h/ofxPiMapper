#pragma once

#include "ofMain.h"
#include "FboSource.h"

class CircleSource : public ofx::piMapper::FboSource {
	public:
    void setup();
		void update();
		void draw();

		std::vector<float> circlesRadius;
		std::vector<float> circlesSpeeds;
};
