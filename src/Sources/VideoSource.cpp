#include "VideoSource.h"

namespace ofx {
    namespace piMapper {
    
        bool VideoSource::enableAudio = false;
        
        VideoSource::VideoSource() {
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
    
        void VideoSource::loadVideo(std::string & filePath) {
            path = filePath;
            setNameFromPath(filePath);
#ifdef TARGET_RASPBERRY_PI
            ofxOMXPlayerSettings settings;
            settings.videoPath = filePath;
            settings.useHDMIForAudio = true;
            settings.enableTexture = true;
            settings.enableLooping = true;
            settings.enableAudio = VideoSource::enableAudio
            omxPlayer = new ofxOMXPlayer();
            omxPlayer->setup(settings);
            texture = &(omxPlayer->getTextureReference());
#else
            videoPlayer = new ofVideoPlayer();
            videoPlayer->loadMovie(filePath);
            videoPlayer->setLoopState(OF_LOOP_NORMAL);
            videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
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
            loaded = false;
        }
    
#ifndef TARGET_RASPBERRY_PI
        void VideoSource::update(ofEventArgs & args) {
            if (videoPlayer != NULL) {
                videoPlayer->update();
            }
        }
#endif
    } // namespace piMapper
} // namespace ofx