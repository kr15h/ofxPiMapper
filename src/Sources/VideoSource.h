#pragma once

#include "ofMain.h"
#include "BaseSource.h"
#ifdef TARGET_RASPBERRY_PI
  #include "ofxOMXPlayer.h"
#endif

namespace ofx {
  namespace piMapper {
    class VideoSource : public BaseSource {
    public:
      VideoSource();
      ~VideoSource();
      std::string& getPath();
      void loadVideo(std::string& path);
      void clear();
#ifndef TARGET_RASPBERRY_PI
      void update(ofEventArgs& args);
#endif
      
    private:
#ifdef TARGET_RASPBERRY_PI
      ofxOMXPlayer* omxPlayer; // Naming different for less confusion
#else 
      // Go with ofVideoPlayer or
      // TODO: High Performance Video player on newer Macs
      ofVideoPlayer* videoPlayer;
#endif
    };
  }
}