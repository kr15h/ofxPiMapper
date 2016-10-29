#pragma once

#include "BaseCmd.h"
#include "TextureEditorWidget.h"

class ofxPiMapper;

namespace ofx {
namespace piMapper {

class SelNextTexCoordCmd : public BaseUndoCmd {

	public:
		SelNextTexCoordCmd(TextureEditorWidget * te);
		void exec();
		void undo();

	private:
		TextureEditorWidget * _textureEditor;
		int _prevSelection;

};

} // namespace piMapper
} // namespace ofx

