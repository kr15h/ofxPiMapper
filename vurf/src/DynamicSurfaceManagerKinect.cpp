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
        //grayThreshNear.threshold(nearThreshold, true);
        //grayThreshFar.threshold(farThreshold);
        //cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);

	//cvSmooth(grayImage.getCvImage(), grayImage.getCvImage(), CV_GAUSSIAN, 2);

	//grayImage.dilate();
	/*grayImage.dilate();
	grayImage.erode();
	grayImage.blur(7);*/
	/*grayImage.erode();
	grayImage.erode();
	grayImage.blur(7);*/


        grayImage.flagImageChanged();

        // set contour tracker parameters
        contourFinder.setMinArea(minArea);
        contourFinder.setMaxArea(maxArea);
        contourFinder.setThreshold(threshold);
        contourFinder.getTracker().setPersistence(persistence);
        contourFinder.getTracker().setMaximumDistance(maxDistance);


	/*contourFinder.setMinAreaRadius(1);
	contourFinder.setMaxAreaRadius(100);
	contourFinder.setThreshold(15);
	contourFinder.getTracker().setPersistence(75);
	contourFinder.getTracker().setMaximumDistance(500);
	contourFinder.getTracker().setSmoothingRate(1);*/


        // determine found contours
        contourFinder.findContours(grayImage);

	//cout << "updated Kinect" << endl;
    }
}

void DynamicSurfaceManagerKinect::gcSurfaces() {
        double threshold = ofGetFrameNum() - (MAX_BLOB_AGE / 3); // * 3);

        // garbage-collect stale surfaces by setting them to 0,0 coords ?
        for (int i = 0 ; i < MAX_DYNAMIC_SURFACES ; i++) {
                //cout << ofGetFrameNum() << ": threshold is " << threshold << ", last used is " << label_map_lastused[i] << endl;
                if ((label_map[i]!=-1 && (label_map_lastused[i] == 0 || label_map_lastused[i] < threshold)) || (label_map[i]==-2)) { //label_map_lastused[i]>0 && label_map_lastused[i] < threshold)) {
                        //cout << ofGetFrameNum() << ": threshold is " << threshold << ", last used is " << label_map_lastused[i] << endl;

                        //cout << ofGetFrameNum() << ": collecting " << i << " because it hasnt been used since " << label_map_lastused[i] << " (was used for " << label_map[i] << ") " << endl;
                        vector<ofVec2f> hidden;
                        for (int x = 0 ; x < MAX_VERTEX ; x++)
                                hidden.push_back(ofVec2f(0,0));//,ofVec2f(0,0),ofVec2f(0,0),ofVec2f(0,0)};
			hidden.push_back(ofVec2f(0,0));
			try {
                        	//piMapper->getApp().getSurfaceManager()->getSurface(i)->setVertices(hidden); //->hide();
				piMapper->getApp().getSurfaceManager()->getSurface(i)->setEnabled(false);
				//piMapper->getApp().selectSurface(i);
				//piMapper->getApp().moveLayerDown();
                        } catch (std::runtime_error& e) {
                                cout << "Caught exception blanking coordinates for dynamic surface #" << i << " (that is, label " << label_map[i] << "): " << e.what() << "\n";
                        }
 
                        //label_map_lastused[i] = 0;
                        //label_map[i] = -1;
                }
        }

}

int DynamicSurfaceManagerKinect::getDynamicSurfaceIndex(int label) {
	/* assume the first 8 surfaces are for dynamic mapping
		//track how long its been since a surface has been updated
		//when its gone over threshold, mark it for reuse
		//if a label already has a mapping, use it
		//if a label doesn't have a mapping, find an empty mapping to use
		//mapping is just an array of ints mapping, value is label index is surface index...
		int label_map[8] = {0,1,2,3,4,5,6,7};
		double label_lastused[8]; 
	*/
	cout << "---" << endl;
	for (int i = 0 ; i < MAX_DYNAMIC_SURFACES ; i++) {
		cout << "slot " << i << " maps to " << label_map[i] << " with lastused " << label_map_lastused[i] << endl;
	}
	cout << "---" << endl;

        double threshold = ofGetFrameNum() - (MAX_BLOB_AGE*5);

	// find pre-existing label mapping?
	for (int i = 0 ; i < MAX_DYNAMIC_SURFACES ; i++) {
		if (label_map[i] == label) {
			label_map_lastused[i] = ofGetFrameNum();
			cout << ofGetFrameNum() << ": updating " << i << " for label " << label << "; set lastused to " << label_map_lastused[i] << endl;
			return i;
		}
	}	

	
	//no mapping found, make one from one that hasn't been used in a while
	for (int i = 0 ; i < MAX_DYNAMIC_SURFACES ; i++) {
		if (label_map[i]==label || (label_map[i]==-1 || (label_map_lastused[i] < threshold))) {
			label_map[i] = label;
			label_map_lastused[i] = ofGetFrameNum();
			cout << ofGetFrameNum() << ": reusing " << i << " for label " << label_map[i] << "; set lastused to " << label_map_lastused[i] << endl;
			return i;
		}
	}
	

	cout << "couldn't find a mapping to use for label " << label << "?!";
	//exit(1);

        /*try {
                //piMapper->getApp().getSurfaceManager()->getSurface(label)->setVertices(stroke);
                //getDynamicSurface(label)->setVertices(stroke);

        	//piMapper->getApp().getSurfaceManager()->getSurface(label)->setVertices(stroke);

        } catch (std::runtime_error& e) {
                cout << "Caught exception updating coordinates for surface #" << i << "(" << label << "): " << e.what() << "\n";
        }*/

}

void DynamicSurfaceManagerKinect::update() {
	//cout << "DynamicSurfaceManagerKinect::update()" << endl;

	gcSurfaces();

	// update from Kinect ...
	updateKinect();

        //vector<ofPoint> stroke;
	vector<ofVec2f> stroke;

	ofxCv::RectTracker& tracker = contourFinder.getTracker();

	//int i = 0;
    	for(int i = 0; i < contourFinder.size(); i++) {
	        // get contour, label, center point, and age of contour
	        vector<cv::Point> points = contourFinder.getFitHex(i);		
		// getContour(i);
	        int label = contourFinder.getLabel(i);
	        ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
	        int age = tracker.getAge(label);

		cout << "age of " << i << " is " << age << endl;
		if (age < MAX_BLOB_AGE/4) {
			cout << "discarding label " << i << " because age is less than " << MAX_BLOB_AGE << endl;
			continue;	// only bother with something that's been tracked for longer than 10ms(?) to avoid flashes
		}

		//ofVec2f old = piMapper->getApp().getSurfaceManager()->getSurface(index)->getVertices();

		piMapper->getApp().getSurfaceManager()->getSurface(i)->setEnabled(true);


		cout << "got hex with points size " << points.size() << endl;
        	for (int j=0; j<points.size(); j++) {
	        	ofVec3f worldPoint = kinect.getWorldCoordinateAt(points[j].x, points[j].y);
	        	ofVec2f projectedPoint = kpt.getProjectedPoint(worldPoint);
                        cout << "[" << i <<" (" << label << ")]: added point " << projectedPoint.x*1024 << ", " << projectedPoint.y*768;
			cout << " from " << points[j].x << "," << points[j].y << endl;
			//projectedPoint = ofVec2f(points[j].x,points[j].y);	
		    	stroke.push_back(projectedPoint * ofVec2f(1024,768)); //ofVec2f(projectedPoint.x,projectedPoint.y));
		}
		stroke.push_back(
			(ofVec2f)kpt.getProjectedPoint(
				(ofVec3f)kinect.getWorldCoordinateAt(points[0].x, points[0].y)
			) * ofVec2f(1024,768)
		);
		//stroke.push_back(ofVec2f(points[0].x,points[0].y)*ofVec2f(1024,768));

		//label = i;	// disable to use labels instead of surfaces .. 
		int index = getDynamicSurfaceIndex(label);

		if (index>-1) {
                	try {
	                        //piMapper->getApp().getSurfaceManager()->getSurface(label)->setVertices(stroke);

				//stroke = lerpVertices(stroke, piMapper->getApp().getSurfaceManager()->getSurface(index)->getVertices());

				piMapper->getApp().getSurfaceManager()->getSurface(index)->setVertices(stroke);

				// move it up a layer
				//piMapper->getApp().selectSurface(index);
				//piMapper->getApp().moveLayerUp();
	                } catch (std::runtime_error& e) {
	                                cout << "Caught exception updating coordinates for contourFinder#object #" << i << "(label " << label << ", surface index " << index << "): " << e.what() << "\n";
        	        }
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
	//double a = ofGetFrameNum();
	for (int i = 0 ; i < MAX_DYNAMIC_SURFACES ; i++) {
		label_map[i] = -2;
		label_map_lastused[i] = 0.0f;//a;//[a,a,a,a,a,a,a,a];
	}
	//label_map_lastused = {0,0,0,0,0,0,0,0};

        //exit(0);      // for checking output
}

