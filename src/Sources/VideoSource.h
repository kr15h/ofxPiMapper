#pragma once

#include "ofMain.h"
#include "BaseSource.h"

#ifdef TARGET_RASPBERRY_PI
 #include "ofxOMXPlayer.h"
 #include "OMXPlayerCache.h"
#endif

namespace ofx {
namespace piMapper {

class VideoSource : public BaseSource {

	public:

		// TODO: Create enableAudio() and disableAudio() methods
		//       for live audio enabling and disabling.
		static bool enableAudio;
		static bool useHDMIForAudio;

		VideoSource();

		string & getPath();
		void loadVideo(string & path);
		void clear();
        void togglePause();

		#ifndef TARGET_RASPBERRY_PI
			void update(ofEventArgs & args);
		#endif

	private:

		#ifdef TARGET_RASPBERRY_PI
			ofxOMXPlayer * _omxPlayer;
		#else
			unique_ptr<ofVideoPlayer> _videoPlayer;
			bool _initialVolumeSet;
		#endif

};

} // namespace piMapper
} // namespace ofx