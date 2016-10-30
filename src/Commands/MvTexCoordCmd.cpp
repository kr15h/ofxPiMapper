#include "MvTexCoordCmd.h"

namespace ofx {
namespace piMapper {

MvTexCoordCmd::MvTexCoordCmd(int texCoordIndex, ofVec2f by){
	_texCoordIndex = texCoordIndex;
	_moveBy = by;
}

void MvTexCoordCmd::exec(){
	ofLogNotice("MvTexCoordCmd", "exec");
	_positionBefore =
		Gui::instance()->getTextureEditorWidget().getJoints()[_texCoordIndex]->position;
	Gui::instance()->getTextureEditorWidget().moveSelection(_moveBy);
}

void MvTexCoordCmd::undo(){
	ofLogNotice("MvTexCoordCmd", "undo");
	// TODO: Set position exactly to the one stored in _positionBefore
	Gui::instance()->getTextureEditorWidget().moveSelection(-_moveBy);
	
	//_texEditor->unselectAllJoints();
	//_texEditor->getJoints()[_jointIndex]->select();
	//_texEditor->getJoints()[_jointIndex]->position = _jointPosition;
	//_texEditor = 0;
}

} // namespace piMapper
} // namespace ofx

