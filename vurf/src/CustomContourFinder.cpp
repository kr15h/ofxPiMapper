#include "ofxCv/ContourFinder.h"
#include "CustomContourFinder.h"
#include "ofxCv/Wrappers.h"
#include "ofGraphics.h"

//class CustomContourFinder;

namespace ofxCv {

        using namespace cv;

	//class CustomContourFinder: public ofxCv::ContourFinder {
	
	vector<cv::Point> CustomContourFinder::getFitHex(unsigned int i) const {
		vector<cv::Point> convexHull = getConvexHull(i);		
		vector<cv::Point> quad = convexHull;
		
		static const unsigned int targetPoints = 6;
		static const unsigned int maxIterations = 16;
		static const double infinity = numeric_limits<double>::infinity();
		double minEpsilon = 0;
		double maxEpsilon = infinity;
		double curEpsilon = 16; // good initial guess
		
		// unbounded binary search to simplify the convex hull until it's 4 points
		if(quad.size() > 6) {
			for(int i = 0; i <(int) maxIterations; i++) {
				approxPolyDP(Mat(convexHull), quad, curEpsilon, true);
				if(quad.size() == targetPoints) {
					break;
				}
				if(quad.size() > targetPoints) {
					minEpsilon = curEpsilon;
					if(maxEpsilon == infinity) {
						curEpsilon = curEpsilon *  2;
					} else {
						curEpsilon = (maxEpsilon + minEpsilon) / 2;
					}
				}
				if(quad.size() < targetPoints) {
					maxEpsilon = curEpsilon;
					curEpsilon = (maxEpsilon + minEpsilon) / 2;
				}
			}
		}
		
		return quad;
    }

    //};
    

}
