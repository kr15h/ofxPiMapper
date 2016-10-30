#include "SelTexCoordCmd.h"

namespace ofx {
namespace piMapper {

SelTexCoordCmd::SelTexCoordCmd(TextureEditorWidget * te, int texCoordIndex){
	_textureEditor = te;
	_texCoordIndex = texCoordIndex;
}

void SelTexCoordCmd::exec(){
	ofLogNotice("SelTexCoordCmd", "exec");
	_prevSelectionIndex = _textureEditor->getSelectedTexCoord();
	_textureEditor->selectTexCoord(_texCoordIndex);
}

void SelTexCoordCmd::undo(){
	ofLogNotice("SelTexCoordCmd", "undo");
	_textureEditor->selectTexCoord(_prevSelectionIndex);
}

} // namespace piMapper
} // namespace ofx

