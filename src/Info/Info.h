#pragma once

#include "ofMain.h"

namespace ofx {
namespace piMapper {

class Info {
	public:
		Info();
	
		void draw();
		void toggle();
		void setText(std::string text);
	
	private:
		bool _visible;
		std::string _text;
};

} // namespace piMapper
} // namespace ofx