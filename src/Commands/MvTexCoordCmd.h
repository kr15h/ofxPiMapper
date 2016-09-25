// MvTexCoordCmd
// Move texture coordinate of a selected surface and be able to undo it
// Created by Krisjanis Rijnieks 2015-05-19

#pragma once

#include "BaseCmd.h"
#include "CircleJoint.h"
#include "TextureEditorWidget.h"

namespace ofx {
namespace piMapper {

class MvTexCoordCmd : public BaseUndoCmd {

	public:
		MvTexCoordCmd(int jointIndex, TextureEditorWidget * texEditor);
		void exec();
		void undo();

	private:
		ofVec2f _jointPosition;
		int _jointIndex;
		TextureEditorWidget * _texEditor;

};

} // namespace piMapper
} // namespace ofx

