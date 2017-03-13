/* 
 * CameraSource
 * Camera source for ofxPiMapper
 * Created by Krisjanis Rijnieks on 25/01/2016
 */

#pragma once

#include "ofMain.h"
#include "FboSource.h"

#ifdef TARGET_RASPBERRY_PI
	#include "ofxRPiCameraVideoGrabber.h"
#endif

class CameraSource : public ofx::piMapper::FboSource {
	public:
		CameraSource();

		void update();
		void draw();

	private:
	
		#ifdef TARGET_RASPBERRY_PI
			OMXCameraSettings _omxCameraSettings;
			ofxRPiCameraVideoGrabber _videoGrabber;
		#else
			ofVideoGrabber _videoGrabber;
		#endif
		int _cameraWidth;
        int _cameraHeight;
		bool _cameraFound;
};