// MvTexCoordCmd
// Move texture coordinate of a selected surface and be able to undo it
// Created by Krisjanis Rijnieks 2015-05-19

#pragma once

#include "BaseCmd.h"
#include "CircleJoint.h"
#include "TextureEditor.h"

namespace ofx{
    namespace piMapper{
        
        class MvTexCoordCmd : public BaseUndoCmd{
        
            public:
                MvTexCoordCmd(int jointIndex, TextureEditor * texEditor);
                void exec();
                void undo();
    
            private:
                ofVec2f _jointPosition;
                int _jointIndex;
                TextureEditor * _texEditor;
            };
        
    } // namespace piMapper
} // namespace ofx

