#include "XSource.h"


XSource::XSource(Display* d, Window win, const std::string& windowName) {
    display = d;
    targetWindow = win;
    name = windowName;
    XGetWindowAttributes(display, targetWindow, &windowAttributes);

}

void XSource::setup(){
    allocate(windowAttributes.width, windowAttributes.height); 
    xFrame.allocate(windowAttributes.width, windowAttributes.height, GL_RGBA);
    image = XGetImage(display, targetWindow, 0, 0, windowAttributes.width, windowAttributes.height, AllPlanes, ZPixmap);
}

// Don't do any drawing here
void XSource::update(){
    xFrame.loadData((unsigned char*)image->data, windowAttributes.width, windowAttributes.height, GL_BGRA);
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void XSource::draw(){
	// Fill FBO with our rects
	ofClear(0);
    if (xFrame.isAllocated()) {
        xFrame.draw(0, 0, fbo->getWidth(), fbo->getHeight());
    } else {
        ofLogError() << "xFrame is not allocated!";
    }

}
