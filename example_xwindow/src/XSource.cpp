#include "XSource.h"


XSource::XSource(Display* d, Window win, const std::string& windowName) {
    display = d;
    targetWindow = win;
    name = windowName;
    XGetWindowAttributes(display, targetWindow, &windowAttributes);

}

void XSource::setup(){
    allocate(windowAttributes.width, windowAttributes.height); 

    std::string pipeline = "ximagesrc xid=" + std::to_string(targetWindow) + " use-damage=false ! "
                           "video/x-raw,format=BGRx,framerate=30/1 ! queue ! "
                           "videoconvert ! video/x-raw,format=RGB ! queue";

    ofLogNotice() << "Initializing GStreamer pipeline: " << pipeline;

    if (!videoUtils.setPipeline(pipeline, OF_PIXELS_RGB, true, windowAttributes.width, windowAttributes.height)) {
        ofLogError() << "GStreamer pipeline failed to initialize!";
        return;
    }
    
    videoUtils.startPipeline();
}

// Don't do any drawing here
void XSource::update(){
    videoUtils.update();
    if (videoUtils.isFrameNew()) {
        videoPixels = videoUtils.getPixels(); // ✅ Get pixel data from GStreamer
        
        if (videoPixels.isAllocated()) {
            // Allocate texture once
            if (!videoTexture.isAllocated()) {
                videoTexture.allocate(videoPixels.getWidth(), videoPixels.getHeight(), GL_RGB);
            }
            // Upload new frame to texture
            videoTexture.loadData(videoPixels);
        }
    }
    //xFrame.loadData((unsigned char*)image->data, windowAttributes.width, windowAttributes.height, GL_BGRA);  
}


void XSource::draw(){
    ofClear(0);

    if (videoTexture.isAllocated()) {
        videoTexture.draw(0, 0, fbo->getWidth(), fbo->getHeight()); // ✅ Draw updated frame
    } else {
        ofLogError() << "Video texture is not allocated!";
    }

}
