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
		ss << "  - Press \"<\" and \">\" to select previous or next vertex\n";
		ss << "  - Press <SPACE> to play/pause the video\n";
		ss << " 3. Projection mapping mode\n";
		ss << "  - Press <,> and <.> to select previous or next surface\n";
		ss << "  - Press \"<\" and \">\" to select previous or next vertex\n";
		ss << "  - Press <t> to add new triangle surface\n";
		ss << "  - Press <q> to add new quad surface\n";
		ss << "  - Press <p> to toggle perspective warping while quad surface selected\n";
		ss << "  - Press <g> to add new grid surface\n";
		ss << "  - Press <[> and <]> to remove or add columns to selected grid surface\n";
		ss << "  - Press <{> and <}> to remove or add rows to selected grid surface\n";
		ss << "  - Press <+> and <-> to scale surface up and down\n";
		ss << "  - Press <9> and <0> to move selected surface one layer up or down\n";
		ss << "  - Press <BACKSPACE> to delete selection\n";
		ss << "  - Press <SPACE> to play/pause the video\n";
		ss << "  - Type  <new> to clear composition\n";
		ss << " 4. Source selection mode\n\n";
		
		ss << "You can switch between the modes by using <1>, <2>, <3> and <4> "
			"keys on the keyboard.\n\n";
		
		ss << "Press <s> to save the composition\n";
		ss << "Press <f> to toggle fullscreen\n";
		ss << "Press <z> to undo\n";
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