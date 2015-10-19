#pragma once

#include "ofMain.h"
#include "BaseSource.h"

#define PIMAPPER_FBO_SOURCE_DEF_NAME "FBO Source"
#define PIMAPPER_FBO_SOURCE_DEF_WIDTH 500
#define PIMAPPER_FBO_SOURCE_DEF_HEIGHT 500

namespace ofx {
    namespace piMapper {

        class FboSource : public BaseSource {
            public:
                FboSource();
                ~FboSource();
      
                // Override these in your custom FBO source
                virtual void setup() {};
                virtual void update() {};
                virtual void draw() {};
                virtual void exit() {};

                // The only method from BaseSource to be overriden
                void clear();

                // App listeners
                void addAppListeners();
                void removeAppListeners();
                void onAppSetup(ofEventArgs & args);
                void onAppUpdate(ofEventArgs & args);
                void onAppDraw(ofEventArgs & args);
                void onAppExit(ofEventArgs & args);
      
            protected:
                ofFbo * fbo;
                void allocate(int width, int height);

                // Some handy getters
                int getWidth();
                int getHeight();
        };

    } // namespace piMapper
} // namespace ofx