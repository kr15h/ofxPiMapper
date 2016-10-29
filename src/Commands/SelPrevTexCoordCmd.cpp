#include "SelPrevTexCoordCmd.h"

namespace ofx {
namespace piMapper {

SelPrevTexCoordCmd::SelPrevTexCoordCmd(TextureEditorWidget * te){
	_textureEditor = te;
}

void SelPrevTexCoordCmd::exec(){
	ofLogNotice("SelPrevTexCoordCmd", "exec");
	_prevSelection = _textureEditor->getSelectedTexCoord();
	_textureEditor->selectPrevTexCoord();
}

void SelPrevTexCoordCmd::undo(){
	ofLogNotice("SelPrevTexCoordCmd", "undo");
	//_textureEditor->selectNextTexCoord();
	_textureEditor->selectTexCoord(_prevSelection);
}

} // namespace piMapper
} // namespace ofx

