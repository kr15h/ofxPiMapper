#include "SelNextTexCoordCmd.h"

namespace ofx {
namespace piMapper {

SelNextTexCoordCmd::SelNextTexCoordCmd(TextureEditorWidget * te){
	_textureEditor = te;
}

void SelNextTexCoordCmd::exec(){
	ofLogNotice("SelNextTexCoordCmd", "exec");
	_prevSelection = _textureEditor->getSelectedTexCoord();
	_textureEditor->selectNextTexCoord();
}

void SelNextTexCoordCmd::undo(){
	ofLogNotice("SelNextTexCoordCmd", "undo");
	//_textureEditor->selectPrevTexCoord();
	_textureEditor->selectTexCoord(_prevSelection);
}

} // namespace piMapper
} // namespace ofx

