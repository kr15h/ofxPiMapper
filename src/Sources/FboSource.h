#pragma once

#include "ofMain.h"
#include "BaseSource.h"

#define PIMAPPER_FBO_SOURCE_DEF_NAME "FBO Source"

namespace ofx {
namespace piMapper {

class FboSource : public BaseSource {

	public:
		FboSource(const int width, const int height);
		~FboSource();
		
		void setup();

		// Override this in your custom FBO source
		virtual void update() = 0;

		void addAppListeners();
		void removeAppListeners();

		void onAppUpdate(ofEventArgs & args);

	protected:
		ofFbo 			fbo_;
		ofEasyCam 		camera_;

		int width_;
		int height_;
};

} // namespace piMapper
} // namespace ofx