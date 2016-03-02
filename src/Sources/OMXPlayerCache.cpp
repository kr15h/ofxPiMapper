#include "OMXPlayerCache.h"

namespace ofx {
namespace piMapper {

OMXPlayerCache * OMXPlayerCache::_instance = 0;

OMXPlayerCache * OMXPlayerCache::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::OMXPlayerCache();
	}
	return _instance;
}

ofxOMXPlayer * OMXPlayerCache::load(string moviePath){
	if(_players.find(moviePath) == _players.end()){
		ofxOMXPlayerSettings settings;
		settings.videoPath = moviePath;
		settings.useHDMIForAudio = true;
		settings.enableTexture = true;
		settings.enableLooping = true;
		settings.enableAudio = VideoSource::enableAudio;
		
		ofxOMXPlayer * p = new ofxOMXPlayer();
		p->setup(settings);
		_players.push_back(p);
		
		return p;
	}
	
	_players[moviePath]->restartMovie();
	return _players[moviePath];
}

void OMXPlayerCache::unload(string moviePath){
	if(_players.find(moviePath) != _players.end()){
		_players[moviePath]->setPaused(true);
	}
}

} // namespace piMapper
} // namespace ofx