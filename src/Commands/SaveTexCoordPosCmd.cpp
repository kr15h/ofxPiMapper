#include "SaveTexCoordPosCmd.h"

namespace ofx {
namespace piMapper {

SaveTexCoordPosCmd::SaveTexCoordPosCmd(int texCoordIndex, ofVec2f position){
	_texCoordIndex = texCoordIndex;
	_position = position;
}

void SaveTexCoordPosCmd::exec(){
	ofLogNotice("SaveTexCoordPosCmd", "exec");
}

void SaveTexCoordPosCmd::undo(){
	ofLogNotice("SaveTexCoordPosCmd", "undo");
	Gui::instance()->getTextureEditorWidget().moveTexCoordTo(_texCoordIndex, _position);
}

} // namespace piMapper
} // namespace ofx

