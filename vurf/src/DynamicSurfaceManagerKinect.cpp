#include "DynamicSurfaceManagerKinect.h"

DynamicSurfaceManagerKinect::DynamicSurfaceManagerKinect(){
}

void DynamicSurfaceManagerKinect::updateKinect() {
    kinect.update();

    if(kinect.isFrameNew()) {
        // process kinect depth image
        grayImage.setFromPixels(kinect.getDepthPixels().getData(), kinect.width, kinect.height);
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(nearThreshold, true);
        grayThreshFar.threshold(farThreshold);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        grayImage.flagImageChanged();

        // set contour tracker parameters
        contourFinder.setMinArea(minArea);
        contourFinder.setMaxArea(maxArea);
        contourFinder.setThreshold(threshold);
        contourFinder.getTracker().setPersistence(persistence);
        contourFinder.getTracker().setMaximumDistance(maxDistance);

        // determine found contours
        contourFinder.findContours(grayImage);

	//cout << "updated Kinect" << endl;
    }
}

void DynamicSurfaceManagerKinect::update() {
	//cout << "DynamicSurfaceManagerKinect::update()" << endl;

	// update from Kinect ...
	updateKinect();

        //vector<ofPoint> stroke;
	vector<ofVec2f> stroke;

	ofxCv::RectTracker& tracker = contourFinder.getTracker();

	//int i = 0;
    	for(int i = 0; i < contourFinder.size(); i++) {
	        // get contour, label, center point, and age of contour
	        vector<cv::Point> points = contourFinder.getFitQuad(i);		
		// getContour(i);
	        int label = contourFinder.getLabel(i);
	        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
	        int age = tracker.getAge(label);

        	for (int j=0; j<points.size(); j++) {
	        	ofVec3f worldPoint = kinect.getWorldCoordinateAt(points[j].x, points[j].y);
	        	ofVec2f projectedPoint = kpt.getProjectedPoint(worldPoint);
                        cout << "[" << i <<" (" << label << ")]: added point " << projectedPoint.x*1024 << ", " << projectedPoint.y*768;
			cout << " from " << points[j].x << "," << points[j].y << endl;
		    	stroke.push_back(projectedPoint * ofVec2f(1024,768)); //ofVec2f(projectedPoint.x,projectedPoint.y));
		}

		label = i;	// disable to use labels instead of surfaces .. 
                try {
                        piMapper->getApp().getSurfaceManager()->getSurface(label)->setVertices(stroke);
                } catch (std::runtime_error& e) {
                                cout << "Caught exception updating coordinates for surface #" << i << "(" << label << "): " << e.what() << "\n";
                }


		//cout << "fitquad: " << contourFinder.getFitQuad(i) << endl;
		//stroke = contourFinder.getFitQuad(i);
		stroke.clear();
	}

	
	// assign objects to Surfaces 

	// and update surface coordinates
}

void DynamicSurfaceManagerKinect::setupKinect(){
    // set up kinect
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();

    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);

    kpt.loadCalibration("calibration.xml");

    // setup gui
    gui.setup("parameters");
    gui.add(nearThreshold.set("nearThresh", 255, 0, 255));
    gui.add(farThreshold.set("farThresh", 85, 0, 255));
    gui.add(minArea.set("minArea", 2000, 0, 5000));
    gui.add(maxArea.set("maxArea", 70000, 15000, 150000));
    gui.add(threshold.set("threshold", 100, 1, 100));
    gui.add(persistence.set("persistence", 100, 1, 100));
    gui.add(maxDistance.set("maxDistance", 32, 1, 100));

}


void DynamicSurfaceManagerKinect::setup (ofxPiMapper *setupPiMapper) {
	cout << "DynamicSurfaceManagerKinect::setup\n";

	piMapper = setupPiMapper;

	// setup kinect input
 	setupKinect();

	// setup bank of Surfaces for using as dynamic surfaces

        //exit(0);      // for checking output
}

