#include "DeselectTexCoordCmd.h"

namespace ofx {
namespace piMapper {

DeselectTexCoordCmd::DeselectTexCoordCmd(TextureEditorWidget * te){
	_textureEditor = te;
}

void DeselectTexCoordCmd::exec(){
	ofLogNotice("DeselectTexCoordCmd", "exec");
	
	_selectedTexCoord = -1;
	vector <CircleJoint *> joints = _textureEditor->getJoints();
	for(unsigned int i = 0; i < joints.size(); ++i){
		if(joints[i]->isSelected()){
			_selectedTexCoord = i;
		}
	}
	
	_textureEditor->unselectAllJoints();
}

void DeselectTexCoordCmd::undo(){
	ofLogNotice("DeselectTexCoordCmd", "undo");
	if(_selectedTexCoord == -1){
		return;
	}
	
	_textureEditor->getJoints()[_selectedTexCoord]->select();
}

} // namespace piMapper
} // namespace ofx

