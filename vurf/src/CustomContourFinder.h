#pragma once

#include "ofxCv/Utilities.h"
#include "ofxCv/Tracker.h"

#include "ofxCv/ContourFinder.h"

namespace ofxCv {

	//class CustomContourFinder;

	//class CustomContourFinder: public ContourFinder {
	class CustomContourFinder: public ContourFinder {
	public:
		vector<cv::Point> getFitHex(unsigned int i) const; //CustomContourFinder();
	};

}
