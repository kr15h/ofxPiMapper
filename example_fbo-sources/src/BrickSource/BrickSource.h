#pragma once

#include "ofMain.h"
#include "FboSource.h"

class BrickSource : public ofx::piMapper::FboSource {
	public:
    void setup();
		void update();
		void draw();

		std::vector<ofRectangle> bricks;
		std::vector<int> brickColor;
		int counter;
};
