#include "SelPrevTexCoordCmd.h"

namespace ofx {
namespace piMapper {

SelPrevTexCoordCmd::SelPrevTexCoordCmd(TextureEditor * te){
	_textureEditor = te;
}

void SelPrevTexCoordCmd::exec(){
	ofLogNotice("SelPrevTexCoordCmd", "exec");
	_textureEditor->selectPrevTexCoord();
}

void SelPrevTexCoordCmd::undo(){
	ofLogNotice("SelPrevTexCoordCmd", "undo");
	_textureEditor->selectNextTexCoord();
}

} // namespace piMapper
} // namespace ofx

