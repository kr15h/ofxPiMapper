#include "VideoSource.h"

namespace ofx {
namespace piMapper {

bool VideoSource::enableAudio = true;
bool VideoSource::useHDMIForAudio = false;

VideoSource::VideoSource(){
	loadable = true;
	loaded = false;
	_loop = true;
	type = SourceType::SOURCE_TYPE_VIDEO;
	#ifdef TARGET_RASPBERRY_PI
		_omxPlayer = 0;
	#else
		_videoPlayer = 0;
		_initialVolumeSet = false;
	#endif
}

void VideoSource::loadVideo(std::string & filePath){
	path = filePath;
	setNameFromPath(filePath);
	
	#ifdef TARGET_RASPBERRY_PI
		_omxPlayer = OMXPlayerCache::instance()->load(filePath);
		texture = &(_omxPlayer->getTextureReference());
	#else
		_videoPlayer = make_unique<ofVideoPlayer>();
		_videoPlayer->load(filePath);
		_videoPlayer->setLoopState(OF_LOOP_NORMAL);
		_videoPlayer->play();
		_videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
		texture = &(_videoPlayer->getTexture());
	#endif
	
	ofAddListener(ofEvents().update, this, &VideoSource::update);
	loaded = true;
}

void VideoSource::setLoop(bool loop){
	_loop = loop;
	#ifndef TARGET_RASPBERRY_PI
		if(_videoPlayer == 0) return;
		if(loop) _videoPlayer->setLoopState(OF_LOOP_NORMAL);
		else _videoPlayer->setLoopState(OF_LOOP_NONE);
	#endif
}

void VideoSource::clear(){
	texture = 0;
	
	#ifdef TARGET_RASPBERRY_PI
		OMXPlayerCache::instance()->unload(path);
	#else
		_videoPlayer->stop();
		_videoPlayer->close();
		_videoPlayer.reset();
		_videoPlayer = 0;
	#endif
	
	ofRemoveListener(ofEvents().update, this, &VideoSource::update);
	loaded = false;
}

void VideoSource::togglePause(){
    #ifdef TARGET_RASPBERRY_PI
        _omxPlayer->togglePause();
    #else
        _videoPlayer->setPaused(!_videoPlayer->isPaused());
    #endif
}

void VideoSource::stop(){
	#ifdef TARGET_RASPBERRY_PI
        _omxPlayer->setPaused(true);
    #else
        _videoPlayer->setPaused(true);
    #endif
}

#ifndef TARGET_RASPBERRY_PI
	void VideoSource::update(ofEventArgs & args){
		if(_videoPlayer != 0){
			if(!_initialVolumeSet){
				if(_videoPlayer->isInitialized()){
					_videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
					_initialVolumeSet = true;
				}
			}
			_videoPlayer->update();
		}
	}
#else
	void VideoSource::update(ofEventArgs & args){
		if(!_loop && _omxPlayer != 0){
			if(_omxPlayer->getCurrentFrame() >= _omxPlayer->getTotalNumFrames() - 1){
				_omxPlayer->setPaused(true);
			}
		}
	}
#endif

} // namespace piMapper
} // namespace ofx
