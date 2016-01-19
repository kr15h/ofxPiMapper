#include "Info.h"

namespace ofx {
namespace piMapper {

Info::Info(){
	_visible = false;
}

void Info::draw(){
	if(_visible){
		stringstream ss;
		ss << "There are 4 modes:\n\n";
		ss << " 1. Presentation mode\n";
		ss << " 2. Texture mapping mode\n";
		ss << " 3. Projection mapping mode\n";
		ss << " 4. Source selection mode\n\n";
		ss << "You can switch between the modes by using <1>, <2>, <3> and <4> "
			"keys on the keyboard.\n\n";
		ss << "Press <t> to add new triangle surface\n";
		ss << "Press <q> to add new quad surface\n";
		ss << "Press <p> to toggle perspective warping while quad surface selected\n";
		ss << "Press <s> to save the composition\n";
		ss << "Press <f> to toggle fullscreen\n";
		ss << "Press <i> to hide this message";
		ofDrawBitmapStringHighlight(ss.str(), 10, 20,
									ofColor(0, 0, 0, 100),
									ofColor(255, 255, 255, 200));
	}
}

void Info::toggle(){
	_visible = !_visible;
}

} // namespace piMapper
} // namespace ofx