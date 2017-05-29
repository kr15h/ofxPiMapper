#pragma once

#include "ofMain.h"
#include "FboSource.h"

#include "DynamicSurfaceManagerKinect.h"

class DSMSource : public ofx::piMapper::FboSource {
	public:
        void setup();
	void setDynamic(DynamicSurfaceManagerKinect *dsm) {
		this->dsm = dsm;
		allocate(dsm->grayImage.getWidth(),dsm->grayImage.getHeight());
	};
		void update();
		void draw();

		vector <ofRectangle> rects;
		vector <float> rectSpeeds;

		DynamicSurfaceManagerKinect *dsm;

};
