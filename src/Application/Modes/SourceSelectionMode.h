#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class SourceSelectionMode : public ApplicationBaseMode {

	public:
		static SourceSelectionMode * instance();
		void setup(Application * app);
		void draw(Application * app);
	
		void onGuiEvent(Application * app, GuiEvent & e){}

	private:
		static SourceSelectionMode * _instance;

};

} // namespace piMapper
} // namespace ofx
