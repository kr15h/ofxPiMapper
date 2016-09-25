// MvAllTexCoordsCmd
// Move all texture coordinates of a selected surface undoable command
// Created by Krisjanis Rijnieks 2015-05-18

#pragma once

#include "BaseCmd.h"
#include "BaseSurface.h"
#include "TextureEditorWidget.h"

namespace ofx {
namespace piMapper {

class MvAllTexCoordsCmd : public BaseUndoCmd {

	public:
		MvAllTexCoordsCmd(BaseSurface * surface, TextureEditorWidget * texEditor);
		void exec();
		void undo();

	private:
		vector <ofVec2f> _texCoords;
		BaseSurface * _surface;
		TextureEditorWidget * _texEditor;

};

} // namespace piMapper
} // namespace ofx

