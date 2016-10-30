#pragma once

#include "BaseCmd.h"
#include "TextureEditorWidget.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelTexCoordCmd : public BaseUndoCmd {

	public:
		SelTexCoordCmd(TextureEditorWidget * te, int texCoordIndex);
		void exec();
		void undo();

	private:
		TextureEditorWidget * _textureEditor;
		int _texCoordIndex;
		int _prevSelectionIndex;

};

} // namespace piMapper
} // namespace ofx

