#include "VideoSource.h"

namespace ofx {
namespace piMapper {

bool VideoSource::enableAudio = false;
bool VideoSource::useHDMIForAudio = false;

VideoSource::VideoSource(){
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_VIDEO;
	#ifdef TARGET_RASPBERRY_PI
		omxPlayer = 0;
	#else
		videoPlayer = 0;
		_initialVolumeSet = false;
	#endif
}

VideoSource::~VideoSource(){}

void VideoSource::loadVideo(string & filePath){
	path = filePath;
	setNameFromPath(filePath);
	#ifdef TARGET_RASPBERRY_PI
		omxPlayer = OMXPlayerCache::instance()->load(filePath);
		texture = &(omxPlayer->getTextureReference());
	#else
		videoPlayer = new ofVideoPlayer();
		videoPlayer->load(path);
		videoPlayer->setLoopState(OF_LOOP_NORMAL);
		videoPlayer->play();
		videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
		texture = &(videoPlayer->getTexture());
		ofAddListener(ofEvents().update, this, &VideoSource::update);
	#endif
	loaded = true;
}

void VideoSource::clear(){
	texture = 0;
	#ifdef TARGET_RASPBERRY_PI
		OMXPlayerCache::instance()->unload(path);
	#else
		ofRemoveListener(ofEvents().update, this, &VideoSource::update);
		videoPlayer->stop();
		videoPlayer->close();
		delete videoPlayer;
		videoPlayer = 0;
	#endif
	loaded = false;
}

void VideoSource::togglePause(){
    #ifdef TARGET_RASPBERRY_PI
        omxPlayer->togglePause();
    #else
        videoPlayer->setPaused(!videoPlayer->isPaused());
    #endif
}

#ifndef TARGET_RASPBERRY_PI
	void VideoSource::update(ofEventArgs & args){
		if(videoPlayer != 0){
			if(!_initialVolumeSet){
				if(videoPlayer->isInitialized()){
					videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
					_initialVolumeSet = true;
				}
			}
			videoPlayer->update();
		}
	}
#endif

} // namespace piMapper
} // namespace ofx