// MvAllTexCoordsCmd
// Move all texture coordinates of a selected surface undoable command
// Created by Krisjanis Rijnieks 2015-05-15

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "TextureEditor.h"

namespace ofx{
    namespace piMapper{
        
        class MvAllTexCoordsCmd : public BaseUndoCmd{
        
            public:
                MvAllTexCoordsCmd(BaseSurface * surface, TextureEditor * texEditor);
                void exec();
                void undo();
    
            private:
                vector<ofVec2f> _texCoords;
                BaseSurface * _surface;
                TextureEditor * _texEditor;
        };
        
    } // namespace piMapper
} // namespace ofx

