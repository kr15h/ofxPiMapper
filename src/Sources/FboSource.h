#pragma once

#include "ofMain.h"
#include <ofxPostGlitch.h>
#include "BaseSource.h"

#define PIMAPPER_FBO_SOURCE_DEF_NAME "FBO Source"

namespace ofx {
namespace piMapper {

class FboSource : public BaseSource {

	public:
		FboSource(const int width, const int height);
		~FboSource();

		// Override these in your custom FBO source
		void setup();
		virtual void update() = 0;
		// virtual void draw(){}
		// virtual void exit(){}

		// App listeners
		void addAppListeners();
		void removeAppListeners();

		void onAppUpdate(ofEventArgs & args);
		void onAppExit(ofEventArgs & args);

	protected:
		void allocate(int width, int height);
		int getWidth();
		int getHeight();

		ofFbo 			fbo_;
		ofxPostGlitch 	glitch_;
		ofEasyCam 		camera_;

		int width_;
		int height_;
};

} // namespace piMapper
} // namespace ofx