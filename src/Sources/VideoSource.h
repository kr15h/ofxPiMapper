#pragma once

#include "ofMain.h"
#include "BaseSource.h"
#ifdef TARGET_RASPBERRY_PI
  /*
   Notice that if you get an error like this:
   fatal error: libavcodec/opt.h: No such file or directory
   Create a file opt.h in addons/ofxOMXPlayer/libs/ffmpeg/libavcodec/
   with the following contents: 
   
   #ifndef AVCODEC_OPT_H
   #define AVCODEC_OPT_H
   #include "libavcodec/version.h"
   #if FF_API_OPT_H
   #include "libavutil/opt.h"
   #endif
   #endif // AVCODEC_OPT_H
   
   More here: https://github.com/jvcleave/ofxOMXPlayer/issues/34
  */
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