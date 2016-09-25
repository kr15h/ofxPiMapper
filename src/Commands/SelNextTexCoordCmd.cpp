#include "SelNextTexCoordCmd.h"

namespace ofx {
namespace piMapper {

SelNextTexCoordCmd::SelNextTexCoordCmd(TextureEditorWidget * te){
	_textureEditor = te;
}

void SelNextTexCoordCmd::exec(){
	ofLogNotice("SelNextTexCoordCmd", "exec");
	_textureEditor->selectNextTexCoord();
}

void SelNextTexCoordCmd::undo(){
	ofLogNotice("SelNextTexCoordCmd", "undo");
	_textureEditor->selectPrevTexCoord();
}

} // namespace piMapper
} // namespace ofx

