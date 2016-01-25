/*
 * CameraSource example
 * Based on the thought that ofxPiMapper should be as bare-bones as possible, thus all the source 
 * type functionality should come from outside.
 * Created by Krisjanis Rijnieks on 25/01/2016
 */

#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "CameraSource.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void draw();

		ofxPiMapper piMapper;
		CameraSource * cameraSource;
};