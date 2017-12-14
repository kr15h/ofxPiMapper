#pragma once

#include "ofMain.h"
#include "BaseSource.h"

#define PIMAPPER_FBO_SOURCE_DEF_NAME "FBO Source"

namespace ofx {
namespace piMapper {

class FboSource : public BaseSource {

	public:
		FboSource();
		~FboSource();

		// Override these in your custom FBO source
		virtual void setup(){}
		virtual void update(){}
		virtual void draw(){}

		// We use this as replacement of draw internally in ofxPiMapper
		// to populate the FBO texture that then can be drawn again by
		// calling normal draw();
		// Or maybe this should be simplified? By leaving only one draw?
		// And the user would have to allocate the fbo himself?
		void updateFbo();
		void drawFbo();
	
		// The only method from BaseSource to be overriden
		void clear();

		// App listeners
		void setDisableDraw(bool b); // Use in cases with external ofFbo

        // fbo accessor functions to allow us to wrap any function with begin/end calls to fbo
        void beginFbo();
        void endFbo();

	protected:
		ofFbo * fbo;
		void allocate(int width, int height);

		// Some handy getters
		int getWidth();
		int getHeight();
	
		bool _disableDraw;
};

} // namespace piMapper
} // namespace ofx
