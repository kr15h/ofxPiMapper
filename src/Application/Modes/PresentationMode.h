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
	
		void onGuiEvent(Application * app, GuiEvent & e){}

	private:
		static PresentationMode * _instance;

};

} // namespace piMapper
} // namespace ofx
