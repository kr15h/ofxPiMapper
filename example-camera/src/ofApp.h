/*
 * CameraSource example
 * Can be used with the Raspberry Pi camera module or the Auvidea HDMI bridge.
 * B101 HDMI to CSI-2 Bridge (15 pin FPC).
 * Available at http://www.auvidea.eu/index.php/theme-styles/2014-12-30-22-32-06/b101
 * Created by Krisjanis Rijnieks on 25/01/2016
 * Last modified on 10/02/2016
 */

#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "CameraSource.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();

		ofxPiMapper piMapper;
		CameraSource * cameraSource;
};