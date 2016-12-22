#include "Info.h"

namespace ofx {
namespace piMapper {

Info::Info(){
	_visible = false;
}

void Info::draw(){
	if(_visible){
		std::string out;
		out + "There are 4 modes:\n\n";
		out + " 1. Presentation mode\n";
		out + " 2. Texture mapping mode\n";
		out + "  - Press \"<\" and \">\" to select previous or next vertex\n";
		out + "  - Press <SPACE> to play/pause the video\n";
		out + " 3. Projection mapping mode\n";
		out + "  - Press <,> and <.> to select previous or next surface\n";
		out + "  - Press \"<\" and \">\" to select previous or next vertex\n";
		out + "  - Press <t> to add new triangle surface\n";
		out + "  - Press <q> to add new quad surface\n";
		out + "  - Press <p> to toggle perspective warping while quad surface selected\n";
		out + "  - Press <g> to add new grid surface\n";
		out + "  - Press <[> and <]> to remove or add columns to selected grid surface\n";
		out + "  - Press <{> and <}> to remove or add rows to selected grid surface\n";
		out + "  - Press <+> and <-> to scale surface up and down\n";
		out + "  - Press <9> and <0> to move selected surface one layer up or down\n";
		out + "  - Press <l> to hide/show layer panel\n";
		out + "  - Press <BACKSPACE> to delete selection\n";
		out + "  - Press <SPACE> to play/pause the video\n";
		out + "  - Type  <new> to clear composition\n";
		out + " 4. Source selection mode\n\n";
		
		out + "You can switch between the modes by using <1>, <2>, <3> and <4> "
			"keys on the keyboard.\n\n";
		
		out + "Press <s> to save the composition\n";
		out + "Press <f> to toggle fullscreen\n";
		out + "Press <z> to undo\n";
		out + "Press <i> to hide this message";
		ofDrawBitmapStringHighlight(out, 10, 20,
									ofColor(0, 0, 0, 100),
									ofColor(255, 255, 255, 200));
	}
}

void Info::toggle(){
	_visible = !_visible;
}

} // namespace piMapper
} // namespace ofx