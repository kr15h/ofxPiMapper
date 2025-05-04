#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "ofGstUtils.h"

class XSource : public ofx::piMapper::FboSource {
	public:

		XSource(Window win, const std::string& windowName);
		~XSource();

    	void setup();
		void update();
		void draw();

	private:

		Window targetWindow;
		ofGstVideoUtils videoUtils;
		ofTexture videoTexture;
		ofPixels videoPixels;
		
};