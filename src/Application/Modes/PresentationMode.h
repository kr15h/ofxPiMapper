#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "SetApplicationModeCmd.h"
#include "ProjectionMappingMode.h"
#include "GuiMode.h"

namespace ofx {
namespace piMapper {

class PresentationMode : public ApplicationBaseMode {

	public:
		static PresentationMode * instance();
		void draw(Application * app);
        void onMousePressed(Application * app, ofMouseEventArgs & args);
		void onKeyPressed(Application * app, ofKeyEventArgs & args);
	
		void onGuiEvent(Application * app, GuiEvent & e){}

	private:
		size_t incIndex(const size_t current, const size_t limit);
		size_t decIndex(const size_t current, const size_t limit);

		static PresentationMode * _instance;

		size_t 	_hintCounter;

		size_t 	_image_idx = 0;
		size_t 	_video_idx = 0;
		size_t 	_fbo_idx = 0;

};

} // namespace piMapper
} // namespace ofx
