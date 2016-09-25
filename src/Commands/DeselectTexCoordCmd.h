#pragma once

#include "BaseCmd.h"
#include "TextureEditorWidget.h"
#include "CircleJoint.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class DeselectTexCoordCmd : public BaseUndoCmd {

	public:
		DeselectTexCoordCmd(TextureEditorWidget * te);
		void exec();
		void undo();

	private:
		TextureEditorWidget * _textureEditor;
		int _selectedTexCoord;

};

} // namespace piMapper
} // namespace ofx

