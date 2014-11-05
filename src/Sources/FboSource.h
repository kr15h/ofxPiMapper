/*
Use this as base class for your generative sources:
 
class YourGenerativeSource : public FboSource {
  // Your code here
}
*/
#pragma once

#include "ofMain.h"
#include "BaseSource.h"

#define PIMAPPER_DEF_FBO_SOURCE_NAME "FBO Source"

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
      
      // Use these to set up FBo itself
      void allocate(int width, int height);
      void clear(); // The only method from BaseSource to be overriden
      
    protected:
      ofFbo* fbo;
    };
  } // namespace piMapper
} // namespace ofx