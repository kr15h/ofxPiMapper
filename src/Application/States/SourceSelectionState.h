#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"
#include "Gui.h"

namespace ofx {
namespace piMapper {

class SourceSelectionState : public ApplicationBaseState {

	public:
		static SourceSelectionState * instance();
		void draw(Application * app);
	
		void onGuiEvent(Application * app, GuiEvent & e){}

	private:
		static SourceSelectionState * _instance;

};

} // namespace piMapper
} // namespace ofx
