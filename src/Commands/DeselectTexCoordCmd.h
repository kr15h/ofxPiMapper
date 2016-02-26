#pragma once

#include "BaseCmd.h"
#include "TextureEditor.h"
#include "CircleJoint.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class DeselectTexCoordCmd : public BaseUndoCmd {

	public:
		DeselectTexCoordCmd(TextureEditor * te);
		void exec();
		void undo();

	private:
		TextureEditor * _textureEditor;
		int _selectedTexCoord;

};

} // namespace piMapper
} // namespace ofx

