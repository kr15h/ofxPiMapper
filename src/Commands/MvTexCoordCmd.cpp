#include "MvTexCoordCmd.h"

namespace ofx{
    namespace piMapper{
        
        MvTexCoordCmd::MvTexCoordCmd(int jointIndex, TextureEditor * texEditor){
            _jointIndex = jointIndex;
            _texEditor = texEditor;
        }

        void MvTexCoordCmd::exec(){
            ofLogNotice("MvTexCoordCmd", "exec");
            _jointPosition = _texEditor->getJoints()[_jointIndex]->position;
        }
        
        void MvTexCoordCmd::undo(){
            ofLogNotice("MvTexCoordCmd", "undo");
            _texEditor->unselectAllJoints();
            _texEditor->getJoints()[_jointIndex]->select();
            _texEditor->getJoints()[_jointIndex]->position = _jointPosition;
            _texEditor = 0;
        }
        
    } // namespace piMapper
} // namespace ofx

