#include "Info.h"

namespace ofx {
namespace piMapper {

Info::Info(){
	_visible = false;
	_text = "There are 4 modes:\n\n"
		" 1. Presentation mode\n"
		" 2. Texture mapping mode\n"
		"  - Press \"<\" and \">\" to select previous or next vertex\n"
		"  - Press <SPACE> to play/pause the video\n"
		" 3. Projection mapping mode\n"
		"  - Press <,> and <.> to select previous or next surface\n"
		"  - Press \"<\" and \">\" to select previous or next vertex\n"
		"  - Press <t> to add new triangle surface\n"
		"  - Press <q> to add new quad surface\n"
		"  - Press <p> to toggle perspective warping while quad surface selected\n"
		"  - Press <g> to add new grid surface\n"
		"  - Press <[> and <]> to remove or add columns to selected grid surface\n"
		"  - Press <{> and <}> to remove or add rows to selected grid surface\n"
		"  - Press <+> and <-> to scale surface up and down\n"
		"  - Press <9> and <0> to move selected surface one layer up or down\n"
		"  - Press <l> to hide/show layer panel\n"
		"  - Press <BACKSPACE> to delete selection\n"
		"  - Press <SPACE> to play/pause the video\n"
		"  - Type  <new> to clear composition\n"
		"  - Type  <ext> to exit to command line interface\n"
		"  - Type  <rbt> to reboot\n"
		"  - Type  <sdn> to shutdown\n"
		" 4. Source selection mode\n\n"
		
		"You can switch between the modes by using <1>, <2>, <3> and <4> "
		"keys on the keyboard.\n\n"
		
		"Press <s> to save the composition\n"
		"Press <z> to undo\n"
		"Press <i> to hide this message";
}

void Info::draw(){
	if(_visible){
		ofDrawBitmapStringHighlight(_text, 10, 20,
									ofColor(0, 0, 0, 100),
									ofColor(255, 255, 255, 200));
	}
}

void Info::toggle(){
	_visible = !_visible;
}

void Info::setText(string text){
	_text = text;
}

} // namespace piMapper
} // namespace ofx
