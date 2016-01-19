#pragma once

#include "ofMain.h"

namespace ofx {
namespace piMapper {

class Info {
	public:
		Info();
	
		void draw();
		void toggle();
	
	private:
		bool _visible;
};

} // namespace piMapper
} // namespace ofx