#pragma once

#include "Application.h"
#include "ofEvents.h"
#include "ofLog.h"
#include "ofGraphics.h"

namespace ofx {
namespace piMapper {

class TextureMappingState : public ApplicationBaseState {

	public:
		static TextureMappingState * instance();
		void draw(Application * app);

	private:
		static TextureMappingState * _instance;

};

} // namespace piMapper
} // namespace ofx
