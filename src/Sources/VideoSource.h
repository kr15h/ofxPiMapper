#pragma once

#include "ofMain.h"
#include "BaseSource.h"

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
		void update(ofEventArgs & args);

	private:
		unique_ptr<ofVideoPlayer> _videoPlayer;
		bool _initialVolumeSet;

};

} // namespace piMapper
} // namespace ofx