#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "ofGstVideoPlayer.h"
#include "ofGstUtils.h"

class XSource : public ofx::piMapper::FboSource {
	public:
		XSource(Display* display, Window win, const std::string& windowName);
    	void setup();
		void update();
		void draw();

		std::vector<ofRectangle> rects;
		std::vector<float> rectSpeeds;

	private:
		Display *display;
		Window targetWindow;
		XImage *image;
		ofTexture xFrame;
		XWindowAttributes windowAttributes;
		ofGstVideoPlayer videoPlayer;
		ofGstVideoUtils videoUtils; // Handles GStreamer video
		ofTexture videoTexture;     // Texture to store video frames
		ofPixels videoPixels;       // Pixel buffer for texture updates
		
};