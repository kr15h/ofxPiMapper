#pragma once

#include "ofMain.h"
#include "FboSource.h"

class CustomSource : public ofx::piMapper::FboSource {
    public:
        CustomSource();

        // These are overrides of FboSource virtual functions.
        // FBO sources are not executing before they have been assigned to a surface.  
        void update();
        void draw(); // You don't have to care about fbo.begin() or fbo.end() here

    private:
        vector<ofRectangle> rects;
        vector<float> rectSpeeds;
};