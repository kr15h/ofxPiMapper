#pragma once

#include "ofMain.h"
#include "BaseSource.h"

#ifdef TARGET_RASPBERRY_PI
 #include "ofxOMXPlayer.h"
#endif

namespace ofx {
namespace piMapper {

class VideoSource : public BaseSource {

	public:

		// TODO: Create enableAudio() and disableAudio() methods
		//       for live audio enabling and disabling.
		static bool enableAudio;

		VideoSource();
		~VideoSource();

		string & getPath();
		void loadVideo(string & path);
		void clear();

		#ifndef TARGET_RASPBERRY_PI
			void update(ofEventArgs & args);
		#endif

	private:

		#ifdef TARGET_RASPBERRY_PI
			ofxOMXPlayer * omxPlayer;     // Naming different for less confusion
		#else
			// Go with ofVideoPlayer or
			// TODO: High Performance Video player on newer Macs
			ofVideoPlayer * videoPlayer;
			bool _initialVolumeSet;
		#endif

};

} // namespace piMapper
} // namespace ofx