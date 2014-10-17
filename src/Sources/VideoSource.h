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
      void update(ofEventArgs& args);
    private:
#ifdef TARGET_RASPBERRY_PI
      // TODO: implement ofxOMXPlayer
      //
      //
      //
#else 
      // Go with ofVideoPlayer or
      // TODO: High Performance Video player on newer Macs
      ofVideoPlayer* videoPlayer;
#endif
    };
  }
}