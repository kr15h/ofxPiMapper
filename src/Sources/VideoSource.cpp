#include "VideoSource.h"

namespace ofx {
namespace piMapper {

bool VideoSource::enableAudio = true;
bool VideoSource::useHDMIForAudio = false;

VideoSource::VideoSource(){
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_VIDEO;
	_videoPlayer = 0;
	_initialVolumeSet = false;
}

void VideoSource::loadVideo(string & filePath){
	path = filePath;
	setNameFromPath(filePath);
	_videoPlayer = make_unique<ofVideoPlayer>();
	
#ifdef TARGET_RASPBERRY_PI
    _videoPlayer->setPixelFormat(OF_PIXELS_NATIVE);
#endif
	
	_videoPlayer->load(filePath);
	_videoPlayer->setLoopState(OF_LOOP_NORMAL);
	_videoPlayer->play();
	_videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
	texture = &(_videoPlayer->getTexture());
	ofAddListener(ofEvents().update, this, &VideoSource::update);
	loaded = true;
}

void VideoSource::clear(){
	texture = 0;
	ofRemoveListener(ofEvents().update, this, &VideoSource::update);
	_videoPlayer->stop();
	_videoPlayer->close();
	_videoPlayer.reset();
	_videoPlayer = 0;
	loaded = false;
}

void VideoSource::togglePause(){
	_videoPlayer->setPaused(!_videoPlayer->isPaused());
}

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

} // namespace piMapper
} // namespace ofx