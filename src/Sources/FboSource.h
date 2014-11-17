/*
Use this as base class for your generative sources:
 
class YourGenerativeSource : public FboSource {
  // Your code here
}
*/
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
      
      // Add/remove calls to update and draw
      // App listeners are added once the source is assigned to at least one surface
      // App listeners are removed once the source is not assigned anywhere
      void addAppListeners();
      void removeAppListeners();
      
      // These are called on app events
      void onAppSetup(ofEventArgs& args);
      void onAppUpdate(ofEventArgs& args);
      void onAppDraw(ofEventArgs& args);
      void onAppExit(ofEventArgs& args);
      
      // Override these in your custom FBO source
      virtual void setup() {}; // Don't do any drawing here
      virtual void update() {}; // Don't do any drawing here
      // You don't need to take care of fbo.begin() and fbo.end() here;
      virtual void draw() {}; // But this is the only place where you shoud do drawing
      virtual void exit() {};
      
      // The only method from BaseSource to be overriden
      void clear();
      
    protected:
      ofFbo* fbo;
      
      // Use this instead fbo->allocate as it sets other source related settings
      // It is protected to force the user to create derived FBO sources from this
      void allocate(int width, int height);
    };
  } // namespace piMapper
} // namespace ofx