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
		void onAppDraw(ofEventArgs & args);
		void onAppExit(ofEventArgs & args);

		void setDisableDraw(bool b); // Use in cases with external ofFbo

	protected:
		ofFbo fbo_;
		ofxPostGlitch glitch_;
		ofEasyCam camera_;

		void allocate(int width, int height);

		// Some handy getters
		int getWidth();
		int getHeight();
	
		bool _disableDraw;

		int width_;
		int height_;
};

} // namespace piMapper
} // namespace ofx