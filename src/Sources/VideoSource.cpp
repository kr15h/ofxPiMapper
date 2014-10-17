#include "VideoSource.h"

namespace ofx {
  namespace piMapper {
    VideoSource::VideoSource() {
      cout << "VideoSource constr" << endl;
      loadable = true;
      loaded = false;
      type = SourceType::SOURCE_TYPE_VIDEO;
      videoPlayer = NULL;
    }
    
    VideoSource::~VideoSource() {}
    
    void VideoSource::loadVideo(std::string& filePath) {
      path = filePath;
      //cout << "loading video: " << filePath << endl;
      setNameFromPath(filePath);
#ifdef TARGET_RASPBERRY_PI
      // TODO: do omx player
      //
      //
      //
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
      ofRemoveListener(ofEvents().update, this, &VideoSource::update);
      texture = NULL;
#ifdef TARGET_RASPBERRY_PI
      // TODO: do omx player
      //
      //
      //
#else
      videoPlayer->stop();
      videoPlayer->close();
      delete videoPlayer;
      videoPlayer = NULL;
#endif
      //path = "";
      //name = "";
      loaded = false;
    }
    
    void VideoSource::update(ofEventArgs &args) {
#ifdef TARGET_RASPBERRY_PI
      // TODO: do omx player
      //
      // probably needs updating as well
      //
#else
      if (videoPlayer != NULL) {
        videoPlayer->update();
      }
#endif
    }
  }
}