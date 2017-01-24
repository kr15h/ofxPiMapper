#pragma once

#include "ofMain.h"

namespace ofx {
namespace piMapper {

class Info {
	public:
		Info();
	
		void draw();
		void toggle();
		void setText(string text);
	
	private:
		bool _visible;
		string _text;
};

} // namespace piMapper
} // namespace ofx