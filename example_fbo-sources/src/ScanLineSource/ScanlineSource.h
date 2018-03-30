#pragma once

#include "ofMain.h"
#include "FboSource.h"

class ScanlineSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();

		std::vector<ofRectangle> rects;
		std::vector<float> rectSpeeds;
};
