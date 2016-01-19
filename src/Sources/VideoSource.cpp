#include "VideoSource.h"

namespace ofx {
namespace piMapper {

bool VideoSource::enableAudio = false;

VideoSource::VideoSource(){
	loadable = true;
	loaded = false;
	type = SourceType::SOURCE_TYPE_VIDEO;
	#ifdef TARGET_RASPBERRY_PI
		omxPlayer = 0;
	#else
		videoPlayer = 0;
	#endif
}

VideoSource::~VideoSource(){}

void VideoSource::loadVideo(string & filePath){
	path = filePath;
	setNameFromPath(filePath);
	#ifdef TARGET_RASPBERRY_PI
		ofxOMXPlayerSettings settings;
		settings.videoPath = filePath;
		settings.useHDMIForAudio = true;
		settings.enableTexture = true;
		settings.enableLooping = true;
		settings.enableAudio = VideoSource::enableAudio;
		omxPlayer = new ofxOMXPlayer();
		omxPlayer->setup(settings);
		texture = &(omxPlayer->getTextureReference());
	#else
		videoPlayer = new ofVideoPlayer();
		videoPlayer->load(filePath);
		videoPlayer->setLoopState(OF_LOOP_NORMAL);
		videoPlayer->setVolume(VideoSource::enableAudio ? 1.0f : 0.0f);
		videoPlayer->play();
		texture = &(videoPlayer->getTexture());
		ofAddListener(ofEvents().update, this, &VideoSource::update);
	#endif
	loaded = true;
}

void VideoSource::clear(){
	texture = 0;
	#ifdef TARGET_RASPBERRY_PI
		omxPlayer->close();
		delete omxPlayer;
		omxPlayer = 0;
	#else
		ofRemoveListener(ofEvents().update, this, &VideoSource::update);
		videoPlayer->stop();
		videoPlayer->close();
		delete videoPlayer;
		videoPlayer = 0;
	#endif
	loaded = false;
}

#ifndef TARGET_RASPBERRY_PI
	void VideoSource::update(ofEventArgs & args){
		if(videoPlayer != 0){
			videoPlayer->update();
		}
	}
#endif

} // namespace piMapper
} // namespace ofx