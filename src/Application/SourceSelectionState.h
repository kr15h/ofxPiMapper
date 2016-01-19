#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
namespace piMapper {

class SourceSelectionState : public ApplicationBaseState {

	public:
		static SourceSelectionState * instance();
		void draw(Application * app);

	private:
		static SourceSelectionState * _instance;

};

} // namespace piMapper
} // namespace ofx
