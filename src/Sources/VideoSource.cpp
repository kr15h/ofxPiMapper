#include "VideoSource.h"

namespace ofx {
  namespace piMapper {
    VideoSource::VideoSource() {
      //cout << "VideoSource constr" << endl;
      loadable = true;
      loaded = false;
      type = SourceType::SOURCE_TYPE_VIDEO;
#ifdef TARGET_RASPBERRY_PI
      omxPlayer = NULL;
#else
      videoPlayer = NULL;

#endif
    }
    
    VideoSource::~VideoSource() {}
    
    void VideoSource::loadVideo(std::string& filePath) {
      path = filePath;
      //cout << "loading video: " << filePath << endl;
      setNameFromPath(filePath);
#ifdef TARGET_RASPBERRY_PI
      // Do things with the OMX player
      ofxOMXPlayerSettings settings;
      settings.videoPath = filePath;
      settings.useHDMIForAudio = true;	//default true
      settings.enableTexture = true;		//default true
      settings.enableLooping = true;		//default true
      settings.enableAudio = false;		//default true, save resources by disabling
      //settings.doFlipTexture = true;		//default false
      omxPlayer = new ofxOMXPlayer();
      omxPlayer->setup(settings);
      texture = &(omxPlayer->getTextureReference());
#else
      // regular ofVideoPlayer
      videoPlayer = new ofVideoPlayer();
      videoPlayer->loadMovie(filePath);
      videoPlayer->setLoopState(OF_LOOP_NORMAL);
      videoPlayer->play();
      texture = &(videoPlayer->getTextureReference());
      ofAddListener(ofEvents().update, this, &VideoSource::update);
#endif
      loaded = true;
    }
    
    void VideoSource::clear() {
      texture = NULL;
#ifdef TARGET_RASPBERRY_PI
      omxPlayer->close();
      delete omxPlayer;
      omxPlayer = NULL;
#else
      ofRemoveListener(ofEvents().update, this, &VideoSource::update);
      videoPlayer->stop();
      videoPlayer->close();
      delete videoPlayer;
      videoPlayer = NULL;
#endif
      //path = "";
      //name = "";
      loaded = false;
    }
    
#ifndef TARGET_RASPBERRY_PI
    void VideoSource::update(ofEventArgs &args) {
      if (videoPlayer != NULL) {
        videoPlayer->update();
      }
    }
#endif
  }
}