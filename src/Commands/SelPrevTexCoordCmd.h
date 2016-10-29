#pragma once

#include "BaseCmd.h"
#include "TextureEditorWidget.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelPrevTexCoordCmd : public BaseUndoCmd {

	public:
		SelPrevTexCoordCmd(TextureEditorWidget * te);
		void exec();
		void undo();

	private:
		TextureEditorWidget * _textureEditor;
		int _prevSelection;

};

} // namespace piMapper
} // namespace ofx

