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
		ofxOMXPlayer * load(string moviePath);
		void unload(string moviePath);

	private:
		static OMXPlayerCache * _instance;
		map <string, ofxOMXPlayer *> _players;

};

} // namespace piMapper
} // namespace ofx

#endif
