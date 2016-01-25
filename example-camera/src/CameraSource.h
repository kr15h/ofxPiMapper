/* 
 * CameraSource
 * Camera source for ofxPiMapper
 * Created by Krisjanis Rijnieks on 25/01/2016
 */

#pragma once

#include "ofMain.h"
#include "FboSource.h"

class CameraSource : public ofx::piMapper::FboSource {
	public:
		CameraSource();

		void update();
		void draw();

	private:
		ofVideoGrabber _videoGrabber;
		int _cameraWidth;
        int _cameraHeight;
		bool _cameraFound;
};