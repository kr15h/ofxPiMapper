#pragma once

#ifdef TARGET_RASPBERRY_PI

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "VideoSource.h"


namespace ofx {
namespace piMapper {

class OMXPlayerCache {

	public:
		static OMXPlayerCache * instance();
		ofxOMXPlayer * load(std::string moviePath);
		void unload(std::string moviePath);

	private:
		static OMXPlayerCache * _instance;
		map <std::string, ofxOMXPlayer *> _players;

};

} // namespace piMapper
} // namespace ofx

#endif
